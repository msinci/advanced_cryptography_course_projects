% des test by MSI 2014
clc;
clear all;


key = round(rand(8,7));
key(:,8) = mod(sum(key,2),2); % note these eight bits of key are never used in encryption
key = reshape(key',1,64);

plain = round(rand(8,7));
plain(:,8) = mod(sum(plain,2),2); % note these eight bits of key are never used in encryption
plain = reshape(plain',1,64);


encrypted=DES(plain,'ENC',key);
decrypted=DES(encrypted,'DEC',key);

plain=reshape(plain,8,8)
encrypted=reshape(encrypted,8,8)
decrypted=reshape(decrypted,8,8)


