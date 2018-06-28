dat=zeros(10,1024);
sav=false;
compt=1;
j=1;
trig=filter([-1 -1 -1 -1 1 1 1 1],1,(data+randn(1,length(VarName1))'));
% trig=filter([1 -1],1,data);
% trig=filter([1 zeros(1,2) -1],1,data);
for i=5:length(data)
%    trig=-(data(i)-data(i-1));
   if trig(i)>20 && compt~=1024
        sav=true;
   end
   if sav
       dat(j,compt)=data(i-2)+randn();
       compt=compt+1;
       if compt==1025
            compt=1;
            j=j+1;
            sav=false;
       end
   end
end

% plot(dat')
plot(VarName1+randn(1,length(VarName1))');hold on;plot(trig,'g');hold on;plot(20*ones(1,length(trig)),'r')
% figure;plot(data)
%%
close all