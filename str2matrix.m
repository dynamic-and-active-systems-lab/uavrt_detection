function [outMat] = str2matrix(inputStr)
%STR2MATRIX Converts a string containing a matrix in Matlab notation to a
%numeric array. Arrays must be no greater than two dimensions. Hard
%brackets should enclose the array, with semicolons separating rows.
%Columns can be separated by white space or commas. All rows must have the
%same number of columns. Note that str2num would produce similar results to
%this function, but is not supported for code generation. 
%
%INPUTS:
%   inputStr    A string containing a matrix. Ex: '[2 3; 5, 6 ;7 ,8 ]'
%OUTPUS:
%   outMat      A numeric array of the input matrix. 
%
%
%Author:    Michael W. Shafer
%Date:      2022-02-15
%--------------------------------------------------------------------------

%Strip redundant white space
done = false;
i = 1;
while ~done
    if i+1 == numel(inputStr)
        done = true;
    end
    if isspace(inputStr(i)) && isspace(inputStr(i+1))
        %inputStr(i+1) = '';
        %inputStr = inputStr(1:numel(inputStr) ~= i+1);
        inputStr(i+1) = [];
        i = i-1;
    end
    i = i+1;
end
%Strip out white space after [ ; and , characters
done = false;
i = 1;
while ~done
    if i+1 == numel(inputStr)
        done = true;
    end
    if inputStr(i)=='[' && isspace(inputStr(i+1))
        inputStr(i+1) = [];
        i = i-1;
	elseif inputStr(i)==',' && isspace(inputStr(i+1))
        inputStr(i+1) = [];
        i = i-1;
    elseif inputStr(i)==';' && isspace(inputStr(i+1))
        inputStr(i+1) = [];
        i = i-1;
    end
    i = i+1;
end

%Strip out white space before [ ; and , characters
inputStr = fliplr(inputStr);
done = false;
i = 1;
while ~done
    if i+1 == numel(inputStr)
        done = true;
    end
    if inputStr(i)=='[' && isspace(inputStr(i+1))
        inputStr(i+1) = [];
        i = i-1;
	elseif inputStr(i)==',' && isspace(inputStr(i+1))
        inputStr(i+1) = [];
        i = i-1;
    elseif inputStr(i)==';' && isspace(inputStr(i+1))
        inputStr(i+1) = [];
        i = i-1;
    end
    i = i+1;
end
inputStr = fliplr(inputStr);
%Replace space with commas for marking columns
inputStr(inputStr == ' ') = ',';


leftBracketLoc = find(inputStr == '[');
rightBracketLoc = find(inputStr == ']');
if numel(leftBracketLoc) ~= 1 || numel(rightBracketLoc) ~= 1
    error('UAV-RT: Matrix string must contain at least and only one left and one right bracket.')
end
semiColLocs = find(inputStr == ';');
rowDividerLocs = sort([leftBracketLoc, semiColLocs, rightBracketLoc]);
numelRows = numel(rowDividerLocs)-1;

commaLocs = find(inputStr == ',');

%Check for the number of columns in the first row to preallocate outMat
charStart = rowDividerLocs(1);
charEnd   = rowDividerLocs(2);
currCommaLocs = commaLocs( commaLocs > charStart & commaLocs < charEnd);
numelCommasCurr = numel(currCommaLocs);
numelCols = numelCommasCurr+1;
outMat = complex(zeros(numelRows,numelCols));

numelCommasLast = 0;
for i = 1:numelRows
    charStart = rowDividerLocs(i);
    charEnd   = rowDividerLocs(i+1);
    currCommaLocs = commaLocs( commaLocs > charStart & commaLocs < charEnd);
    numelCommasCurr = numel(currCommaLocs);
    
    if i>1 && (numelCommasCurr ~= numelCommasLast)
        error('UAV-RT: Different numer of columns in different rows.')
    end
    
    colDividerLocs = [charStart,currCommaLocs,charEnd];
    
    tempRow = complex(zeros(1,numelCommasCurr+1));
    
    for j = 1:numel(colDividerLocs)-1
        tempNum = str2double(inputStr(colDividerLocs(j)+1:colDividerLocs(j+1)-1));
        tempRow(j) = tempNum;
    end
    outMat(i,:) = tempRow;
    
    numelCommasLast = numelCommasCurr;
    

end

