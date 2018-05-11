% MSI TMTO implementation for DES 56 
clc;
clear all;  % clearing all the workspace variables

plain = round(rand(8,8));   % creating a random plaintext
plain = reshape(plain',1,64);
randkey = round(rand(8,7)); % creating a random key that will be our secret key
randkey(:,8) = mod(sum(randkey,2),2);
randkey = reshape(randkey',1,64);

for x=44:100    
hellman_table = zeros(1024,1,64);  
% the table that'll hold the starting points, SPs and ending points, EPs

display('creating the hellman table with random starting points');

for i=1:1024
    key = round(rand(8,7));
    key(:,8) = mod(sum(key,2),2);
    key = reshape(key',1,64);
    hellman_table(i,1,:)=key;   % first column of the table stores random keys 
                                % each row corresponds to a new chain
end

display('table created!')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   ENDPOINT CALCULATION %   ENDPOINT CALCULATION %   ENDPOINT CALCULATION %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for j=1:1024    % using the formula P(S)>= mt / N we calculate the m(row count)
                % P(S) here being the probability of success
        j
        encrypted = hellman_table(j,:);
        key56 = reduct(encrypted);
        notzero=1;
%       chainlength=0;  % i was planning on storing the chainlength for
%       each chain as well but then i decided not to because the matlab
%       time analysis showed that it slows down the process considerably

        while notzero   % when the last 6 bits are not zero, 
                        % which indicates that the distinguished point has not been reached
                        % the operation continues
            
            encrypted=DES(plain,'ENC',key56);   
            key56 = reduct(encrypted);  % zeroing the first 26 bits and eliminating the parity
            notzero = any(key56(51:56));
%           chainlength=chainlength+1;

        end
%       sprintf('length of this chain is %d', chainlength);        
        hellman_table(j,2,:)=addparity(key56); % adding parity bits when an EP is found 
                                                 % and storing it in the table
end

display('ending points calculations are done');

fname = sprintf('table_%d.mat', x);
save (fname, 'hellman_table');

save('all'); % saving all the variables since creating the table takes about 1 hour
                     % and it's too risky to keep them in volatile memory 

end

   

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%   Distinguished point search for the key

    notzero=1;
    chainlength=0;
    encrypted=randkey;
    randkey56 = reduct(encrypted);
    while notzero   % here we encrypt until we find the distinguished point for the known cyphertext
        encrypted=DES(plain,'ENC',randkey56);
        randkey56 = reduct(encrypted);
        notzero = any(randkey56(51:56));
        chainlength=chainlength+1;
    end
    randdp=addparity(randkey56);
    chainlength;

% sorted_table=sort(hellman_table,2); % sort the table according to the EPs
        
    match=0;
    l=0;    % l here is our row counter
	while(~match) % when a match is found between EPs and the randkeyEP, it meaans 
                  % that the secret key is in the l th 
        l=l+1
        match=isequal(hellman_table(l,2,:),randdp(1,:));
%         match=isequal(hellman_table(3,2,:),randdp(:));
    end
    
% display('match is found!');    
% sorted_table(l,2,:)    

    