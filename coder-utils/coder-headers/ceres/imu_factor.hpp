// Copyright 2021-2022 The MathWorks, Inc.
#ifndef IMU_FACTOR_HPP
#define IMU_FACTOR_HPP

#include <vector>
#include <initializer_list>
#include <unordered_map>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "ceres/ceres.h"

#ifdef BUILDING_LIBMWCERESCODEGEN
    #include "cerescodegen/cerescodegen_spec.hpp"
    #include "cerescodegen/custom_local_parameterization.hpp"
    #include "cerescodegen/factor.hpp"
#else
    /* To deal with the fact that PackNGo has no include file hierarchy */
    #include "cerescodegen_spec.hpp"
    #include "custom_local_parameterization.hpp"
    #include "factor.hpp"
#endif

namespace mw_ceres {

// Implementation of FactorIMU is based on details in [1]
// [1] C. Foster, L. Carlone, F. Dellaert and D. Scaramuzza, "On-Manifold Preintegration
//     for Real-Time Visual-Inertial Odometry," IEEE Transactions on Robotics, Vol. 33, No. 1,
//     pp. 1-21, Feb. 2017, doi: 10.1109/TRO.2016.2597321
//
// See more details at https://ieeexplore.ieee.org/document/7557075

    class IMUCostAD {
    public:
        IMUCostAD(const Eigen::Vector3d& dPos, const Eigen::Quaterniond& dQuat, const Eigen::Vector3d& dVel,
                  const Eigen::Vector3d& g, double dT,
                  const Eigen::Matrix3d& dPdBg, const Eigen::Matrix3d& dPdBa, 
                  const Eigen::Matrix3d& dRdBg,
                  const Eigen::Matrix3d& dVdBg, const Eigen::Matrix3d& dVdBa, 
                  const Eigen::Vector3d& biasGBar, const Eigen::Vector3d& biasABar,  
                  const Eigen::Matrix<double,9,9>& dCov,
                  const Eigen::Matrix<double,6,6>& bCov ) : m_DeltaPos(dPos), m_DeltaQ(dQuat), m_DeltaVel(dVel), m_G(g), m_Duration(dT),
                        m_dPdBg(dPdBg), m_dPdBa(dPdBa), m_dRdBg(dRdBg), m_dVdBg(dVdBg), m_dVdBa(dVdBa), 
                        m_BiasGyroBar(biasGBar), m_BiasAccBar(biasABar){
            m_SqrtDeltaInformation = dCov.inverse().llt().matrixL();            // already is discrete-time noise covariance
            m_SqrtBiasProcessInformation = (bCov).inverse().llt().matrixL();    // already is discrete-time noise covariance
        }

        template <typename T>
        bool operator()(const T* const pose_i,
            const T* const vel_i,
            const T* const bias_i,
            const T* const pose_j,
            const T* const vel_j,
            const T* const bias_j,
            T* residuals) const {

            Eigen::Map<const Eigen::Matrix<T, 3, 1>> pi(pose_i);
            Eigen::Map<const Eigen::Matrix<T, 3, 1>> pj(pose_j);

            Eigen::Map<const Eigen::Quaternion<T>> qi(pose_i + 3);
            Eigen::Map<const Eigen::Quaternion<T>> qj(pose_j + 3);

            Eigen::Map<const Eigen::Matrix<T, 3, 1>> vi(vel_i);
            Eigen::Map<const Eigen::Matrix<T, 3, 1>> vj(vel_j);

            Eigen::Map<const Eigen::Matrix<T, 3, 1>> bgi(bias_i);
            Eigen::Map<const Eigen::Matrix<T, 3, 1>> bai(bias_i + 3);

            Eigen::Map<const Eigen::Matrix<T, 3, 1>> bgj(bias_j);
            Eigen::Map<const Eigen::Matrix<T, 3, 1>> baj(bias_j + 3);

            // tweak pre-integrated measurements with delta bias update

            Eigen::Matrix<T, 3, 1> dBg = bgi - m_BiasGyroBar.cast<T>();
            Eigen::Matrix<T, 3, 1> dBa = bai - m_BiasAccBar.cast<T>();

            Eigen::Matrix<T, 3, 1> tmp = m_dRdBg.cast<T>()* dBg;
            Eigen::Matrix<T, 3, 3> deltaRotCorrection = mw_ceres::SO3::expm<T>(tmp);
            Eigen::Quaternion<T> deltaQCorrection(deltaRotCorrection);
            deltaQCorrection.normalize();

            Eigen::Quaternion<T> correctedDeltaQ = m_DeltaQ.cast<T>() * deltaQCorrection;

            Eigen::Matrix<T, 3, 1> correctedDeltaVel = m_DeltaVel.cast<T>() + m_dVdBg.cast<T>() * dBg + m_dVdBa.cast<T>() * dBa;
            Eigen::Matrix<T, 3, 1> correctedDeltaPos = m_DeltaPos.cast<T>() + m_dPdBg.cast<T>() * dBg + m_dPdBa.cast<T>() * dBa;

            Eigen::Map<Eigen::Matrix<T, 15, 1>> res(residuals);

            // navState residuals
            Eigen::Matrix<T, 9, 1> resNavState;
            T dT = static_cast<T>(m_Duration); // t_ij
            resNavState.template block<3, 1>(0, 0) = qi.inverse() * (pj - pi - vi * dT - static_cast<T>(0.5) * m_G.cast<T>() * dT * dT) - correctedDeltaPos; // position
            resNavState.template block<3, 1>(3, 0) = static_cast<T>(2.0) * (correctedDeltaQ.inverse() * (qi.inverse() * qj)).vec(); // orientation
            resNavState.template block<3, 1>(6, 0) = qi.inverse() * (vj - vi - m_G.cast<T>() * dT) - correctedDeltaVel; // velocity

            res.template block<9, 1>(0, 0) = m_SqrtDeltaInformation * resNavState;

            // noise model
            Eigen::Matrix<T, 6, 1> resBias;
            resBias.template block<3, 1>(0, 0) = bgj - bgi;
            resBias.template block<3, 1>(3, 0) = baj - bai;
            res.template block<6, 1>(9, 0) = m_SqrtBiasProcessInformation * resBias;

            return true;
        }

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    protected:
        Eigen::Vector3d m_DeltaPos;
        Eigen::Quaterniond m_DeltaQ;
        Eigen::Vector3d m_DeltaVel;


        Eigen::Vector3d m_G;
        double m_Duration;

        Eigen::Matrix3d m_dPdBg;
        Eigen::Matrix3d m_dPdBa;
        Eigen::Matrix3d m_dRdBg;
        Eigen::Matrix3d m_dVdBg;
        Eigen::Matrix3d m_dVdBa;



        Eigen::Vector3d m_BiasGyroBar;
        Eigen::Vector3d m_BiasAccBar; // nominal bias values

        Eigen::Matrix<double, 9, 9> m_SqrtDeltaInformation;
        Eigen::Matrix<double, 6, 6> m_SqrtBiasProcessInformation;
    };

    // FactorIMU has the same interface as gtsam::CombinedImuFactor but it does not do the same thing.
    // FactorIMU is equivalent to gtsam::ImuFactor plus an embedded "bewtween" factor for biases
    class CERESCODEGEN_API FactorIMU : public Factor {
    public:
        FactorIMU(int* ids, double sampleRate,
            double* gravityAcceleration,
            double* gyroBiasNoise,
            double* accelBiasNoise,
            double* gyroNoise,
            double* accelNoise,
            double* gyroReadings,
            double* accelReadings,
            size_t numReadings ) : Factor(std::vector<int>(ids,ids+6),
            std::vector<int>{ 7, 3, 6, 7, 3, 6 },
            std::vector<int>{VariableType::Pose_SE3,
                                        VariableType::Vel_3,
                                        VariableType::IMU_Bias,
                                        VariableType::Pose_SE3,
                                        VariableType::Vel_3,
                                        VariableType::IMU_Bias} ) {
            // accel and gyro are expected to have same length by this internal utility. 
            // The user-facing function is responsible for this verification. 
            assert(numReadings % 3 == 0); // sanity check
            m_GyroReadings = std::vector<double>(gyroReadings, gyroReadings+numReadings);
            m_AccelReadings = std::vector<double>(accelReadings, accelReadings+numReadings);

            m_DeltaT = 1.0 / sampleRate;

            m_GyroscopeNoise = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>(gyroNoise); // input data vector is assumed row-major
            m_AccelerometerNoise = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>(accelNoise); // input data vector is assumed row-major

            m_GyroscopeBiasNoise = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>(gyroBiasNoise); // input data vector is assumed row-major
            m_AccelerometerBiasNoise = Eigen::Matrix<double, 3, 3, Eigen::RowMajor>(accelBiasNoise); // input data vector is assumed row-major

            m_GravityAcceleration = Eigen::Vector3d(gravityAcceleration);

            m_PreIntegCovariance = Eigen::Matrix<double, 9, 9>::Zero();
            m_BiasRandWalkCovariance = Eigen::Matrix<double, 6, 6>::Zero();
        }

        // routine to perform before each optimization
        // IMU pre-integration happens here
        void preOptimizationUpdate(std::vector<double*>& currVariableStates) override;

        // invoked at the beginning of every graph optimization
        ceres::CostFunction* createFactorCostFcn() const override {
            return new ceres::AutoDiffCostFunction<IMUCostAD, 15, 7, 3, 6, 7, 3, 6>(
                new IMUCostAD(m_PreIntegratedPos, m_PreIntegratedQuat, m_PreIntegratedVel, m_GravityAcceleration, m_SumDeltaT, m_dPos_dBg, m_dPos_dBa, m_dRot_dBg,
                              m_dVel_dBg, m_dVel_dBa, m_NominalBiasGyro, m_NominalBiasAcc,  m_PreIntegCovariance, m_BiasRandWalkCovariance));
        }

        ceres::LocalParameterization* getVariableLocalParameterization(int variableID) override {
            if (m_MapVariableLPTypes.find(variableID)->second == VariableType::Pose_SE3)
                return new ceres::ProductParameterization( new ceres::IdentityParameterization(3),
                         new ceres::EigenQuaternionParameterization());
            else if (m_MapVariableLPTypes.find(variableID)->second == VariableType::Vel_3)
                return new ceres::IdentityParameterization(3);
            else
                return new ceres::IdentityParameterization(6);
        }

        vector<double> getDefaultState(int variableID) const override {
            if (m_MapVariableLPTypes.find(variableID)->second == VariableType::Pose_SE3)
                return { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
            else if (m_MapVariableLPTypes.find(variableID)->second == VariableType::Vel_3)
                return { 0.0, 0.0, 0.0 };
            else
                return { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        }

        std::string getVariableTypeString(int variableID) const override {
            return VariableTypeString.at(static_cast<VariableType>(getVariableType(variableID)));
        }

        // A utility that helps set initial states during graph optimization,
        // the internal states of this factor should not be affected
        void predict(const double* prevBias, const double* prevPose, const double* prevVel,
            double* predictedPose, double* predictedVel) const;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    protected:

        std::vector<double> m_GyroReadings;
        std::vector<double> m_AccelReadings;

        double m_DeltaT;

        Eigen::Matrix3d m_GyroscopeBiasNoise;

        Eigen::Matrix3d m_AccelerometerBiasNoise;

        Eigen::Matrix3d m_GyroscopeNoise;

        Eigen::Matrix3d m_AccelerometerNoise;

        /** Gravity acceleration vector in inertial frame*/
        Eigen::Vector3d m_GravityAcceleration;

    protected:
        // intermediate internal states, needed to create the residual cost

        Eigen::Quaterniond m_PreIntegratedQuat;
        Eigen::Vector3d m_PreIntegratedPos;
        Eigen::Vector3d m_PreIntegratedVel;
        Eigen::Matrix<double, 9, 9> m_PreIntegCovariance;
        Eigen::Matrix<double, 6, 6> m_BiasRandWalkCovariance;

        Eigen::Vector3d m_NominalBiasAcc;
        Eigen::Vector3d m_NominalBiasGyro;

        double m_SumDeltaT;

        Eigen::Matrix3d m_dRot_dBg;
        Eigen::Matrix3d m_dVel_dBg;
        Eigen::Matrix3d m_dVel_dBa;
        Eigen::Matrix3d m_dPos_dBg;
        Eigen::Matrix3d m_dPos_dBa;
 
    };



}


#endif
