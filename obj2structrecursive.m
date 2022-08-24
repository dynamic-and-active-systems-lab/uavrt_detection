function [structOut] = obj2structrecursive(theInput)
%theInput must either be an object or a structure

if isobject(theInput)
    %get the property names
    %structIn = struct(theInput);
    theFieldNames = properties(theInput);
else
    %structIn = theInput;
    theFieldNames = fieldnames(theInput);
end

numFields = numel(theFieldNames);
%For code generation the left hand side of the definition of structOut
%can't have an parentheses indexing for the first time through field
%access. First define the structOut for the first element as a template,
%then use repmat to generate the correctly size struct array. Then set all
%the array elements.
for i = 1:numFields
    currElement = theInput(1).(theFieldNames{i});
    if isobject(currElement) | isstruct(currElement)
        structOutTemplate.(theFieldNames{i}) = obj2structrecursive(currElement);
    else
        structOutTemplate.(theFieldNames{i}) = currElement;
    end
end

structOut = repmat(structOutTemplate, size(theInput));

for j = 2:numel(theInput)
    for i = 1:numFields
        currElement = theInput(j).(theFieldNames{i});
        if isobject(currElement) | isstruct(currElement)
            structOut(j).(theFieldNames{i}) = obj2structrecursive(currElement);
        else
            structOut(j).(theFieldNames{i}) = currElement;
        end
    end
end

%structOut = reshape(structOut,size(theInput));
end


