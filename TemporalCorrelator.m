classdef TemporalCorrelator < handle
    %UNTITLED7 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        %Inputs to object
        pri            %Baseline repetition interval in time windows (N)
        priUncert      %Number of time windows of uncertainty to search around (M)
        priJtr         %Number of time windows of jitter to consider (J)
        %reps           %Number of repetitions to search for (K)
        
        %Set by constructor
        priMeansList   %Vector of mean repetition intervals for search.
        priJtrList     %Vector of jitter searches around means
             
        %Wq             %The temporal correlation matrix
    end
    
    methods
        function obj = TemporalCorrelator(pri, priUncert, priJtr)%, reps)
            %UNTITLED7 Construct an instance of this class
            %   Detailed explanation goes here
            if nargin>0
                [priSorted, priUncertSorted, priJtrSorted] = formatinputs(pri, priUncert, priJtr);%, reps);
                obj.setprops(priSorted, priUncertSorted, priJtrSorted);%, repsSorted);
            else
                obj.pri         = 0;
                obj.priUncert   = 0;
                obj.priJtr      = 0;
                obj.priMeansList= 0;
                obj.priJtrList  = 0;
                %obj.reps        = [];
                %obj.Wq          = [];
            end
        end
        
        function [] = update(obj, pri, priUncert, priJtr)%, reps)
            %[priSorted, priUncertSorted, priJtrSorted, repsSorted] = formatinputs(pri, priUncert, priJtr, reps);
            [priSorted, priUncertSorted, priJtrSorted] = formatinputs(pri, priUncert, priJtr);%, reps);
            
            priChangedLogic       = any(priSorted~=obj.pri);
            priUncertChangedLogic = any(priUncertSorted~=obj.priUncert);
            priJtrChangedLogic    = any(priJtrSorted~=obj.priJtr);
            %repsChangedLogic      = any(repsSorted~=obj.reps);
            
            changeLogic = any([priChangedLogic, priUncertChangedLogic , priJtrChangedLogic]);%, repsChangedLogic]);
            
            if changeLogic
                obj.setprops(priSorted, priUncertSorted, priJtrSorted);%, repsSorted);
                %disp('updated!')
            %else
                %disp('no update needed!')
            end           
        end
        
        function [Wq] = Wq(obj,reps)
            n = numel(obj.pri);
            if numel(reps)~=n
                error('UAV-RT: Number of elements in the repetition vector (K) must be equal to the number of elements in the PRI property of this object.')
            end
            Wq = [];
            for i = 1:n
                              
                WqTemp = assembleWq(obj.priMeansList(i,:), obj.priJtrList(i,:), reps(i));%, obj.reps(i));
                if i ~=1
                    [numWqRows, numWqCols]          = size(Wq);
                    [numWqTempRows, numWqTempCols]  = size(WqTemp);
                    diffRows = numWqRows - numWqTempRows;
                    if diffRows > 0
                        WqTemp = [WqTemp;sparse(zeros(diffRows,numWqTempCols))];
                    elseif diffRows < 0
                        Wq = [Wq;sparse(zeros(-diffRows,numWqCols))];
                    end
                    Wq = [Wq, WqTemp];
                else
                    Wq = WqTemp;
                end
            end
        end
        
        
        function [] = setprops(obj,priSorted, priUncertSorted, priJtrSorted)%, repsSorted)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            %Set props
            obj.pri       = priSorted;
            obj.priUncert = priUncertSorted;
            obj.priJtr    = priJtrSorted;
            %obj.reps      = repsSorted;
            
            n = numel(priSorted);
            %obj.Wq = [];
            for i = 1:n
                %Change neams to align with other code.
                N = priSorted(i);
                M = priUncertSorted(i);
                J = priJtrSorted(i);
                %K = repsSorted(i);
                if ~isempty(obj.priMeansList)
                    obj.priMeansList(i,:)   = N+(-M:M);
                else
                    obj.priMeansList   = N+(-M:M);
                end
                if ~isempty(obj.priJtrList)
                    obj.priJtrList(i,:)     = -J:J;
                else
                    obj.priJtrList     = -J:J;
                end
            end
        end
    end
end


%function [priSorted, priUncertSorted, priJtrSorted, repsSorted] = formatinputs(pri, priUncert, priJtr, reps)
function [priSorted, priUncertSorted, priJtrSorted] = formatinputs(pri, priUncert, priJtr)
            %First check to make sure all inputs contain the same number of
            %elements
            numelOfInputsVec = [numel(pri),...
                numel(priUncert),...
                numel(priJtr)];%,...
                %numel(reps)];
            if numel(unique(numelOfInputsVec))~=1
                error('UAV-RT: All elements must have the same number of elements')
            else
                n = numel(pri);
            end
            [priSorted,sortInds]  = sort(pri(:));
            priUncertSorted       = priUncert(sortInds);
            priJtrSorted          = priJtr(sortInds);
            %repsSorted            = reps(sortInds);
end

