N=length(test)/1093;
s=zeros(1,length(test));
a=zeros(N,1093);
b=zeros(1,N);
c=zeros(1,N);
m=1093/2;
for i=1:N
    a(i,:)=test((i-1)*1093+1:i*1093);
    [A,B]=max(a(i,:));
    b(i)=B;
%     c(i)=test(B+1093*(i-1),2)-test(1:1093:end,2);
end
% plot(a')
% figure
% plot(test(:,1))
plot(b)
% plot(c)
% plot(b(2:end-1)-b(1:end-2))
% plot(b(1:end-1))
% hold on;
% plot(c(1:end-1)+1,'r')
%%
% plot(a')
% figure
% plot(b(1:end-1))
% figure
% plot(test(:,2))
for i=1:N
    s((i-1)*1093+b(i))=max(test(:,1));
end
% figure
% plot(test(:,1))
% hold on;
% plot(s,'r')
plot(b)