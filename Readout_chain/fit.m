
Nfit=3;
X=zeros(Nfit,3);
for i=1:Nfit
    for j=1:3
       X(i,j)=((i-1)-floor(Nfit/2))^(3-j);
    end
end
Y=data5(Nfit*20+1:end);
Z=zeros(length(Y),1);
T=zeros(length(Y),1);
U=zeros(length(Y),1);
for i=1:length(Y)/Nfit
    C=(X'*X)\X'*Y((i-1)*Nfit+1:i*Nfit);
    Z((i-1)*Nfit+1:i*Nfit)=(X*C);
    T((i-1)*Nfit+1:i*Nfit)=Y(2+(i-1)*3)*ones(3,1);
    U((i-1)*Nfit+1:i*Nfit)=(C(3)-C(2)/(2*C(1)))*ones(3,1);
end
figure;
plot(Z(1:end-10))
hold on
plot(Y(1:end-10),'r')
plot(T(1:end-10),'g')
plot(U(1:end-10),'c')
t=T(1:end-10);
u=U(1:end-10);
sqrt(mean((t-mean(t)).^2))
sqrt(mean((u-mean(u)).^2))
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
