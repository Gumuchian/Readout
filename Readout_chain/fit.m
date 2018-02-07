
Nfit=10;
X=zeros(Nfit,3);
for i=1:Nfit
    for j=1:3
       X(i,j)=((i-1)-floor(Nfit/2))^(3-j);
    end
end
Y=VarName5(3*20+1:end);
Z=zeros(length(Y),1);
for i=1:length(Y)/Nfit
    C=(X'*X)\X'*Y((i-1)*Nfit+1:i*Nfit);
    Z((i-1)*Nfit+1:i*Nfit)=(X*C);
end
figure;
plot(Z(1:end-10))
hold on
plot(Y(1:end-10),'r')
title('Output of the optimal filter /N_{fit} with fit')

%%
A=[5261.68 5260.56 5260.27 5260.28 5260.39 5260.6 5260.9 5261.29 5261.77 5262.35;-60 -30 -10 0 10 20 30 40 50 60];
Nfit=length(A);
X=zeros(Nfit,3);
for i=1:Nfit
    for j=1:3
       X(i,j)=A(2,i)^(3-j);
    end
end
Y=A(1,:)/5260.28;
C=(X'*X)\X'*Y';
Z=X*C;
figure;
plot(Z)
hold on
plot(Y,'r')
