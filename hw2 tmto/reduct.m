function [ output ] = reduct( input )  
    % this reduction function gets rid of the parity bits in the cypertext
    % and returns a 56 bit value
    % it also turns the first 26 bits of the key into zeros since that is
    % the scenario for the assignment
    
output(:,:)=input([1:7,9:15,17:23,25:31,33:39,41:47,49:55,57:63]);
output(1:26) = zeros;

end

