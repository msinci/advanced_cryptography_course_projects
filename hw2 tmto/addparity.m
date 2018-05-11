function [ K ] = addparity ( key )
    % this function calculates and adds the proper party bits to a 56bit
    % key
    K = reshape(key,7,8)';      % taking the transpose of the matrix
    K(:,8) = mod(sum(K,2),2);	% calculating the parity 
                                % note these eight bits of key are never used in encryption
    K = reshape(K',1,64);
    
end

