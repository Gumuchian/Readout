datap=data_pulse(155200:end);
offset=mean(data_pulse(1:155199));
datap=offset-datap;
% plot(datap)
d=zeros(1,2048);
sp=zeros(1,2048);
sn=zeros(1,2048);
save=false;
count=1;
n=0;
for i=1:length(datap)
   if datap(i)>10
      save=true;
   end
   if save
       d(count)=datap(i-10);
       count=count+1;
       if count==2049
            count=1;
            save=false;
            sp=sp+abs(fft(d)/2048);
            n=n+1;
       end
   end
end
sp=sp/n;
n1=floor(length(datan)/2048);

sn=zeros(1,2048);
datan=datan-mean(datan);
for i=1:n1
   sn=sn+abs(fft(datan((i-1)*2048+1:i*2048))/2048)'; 
end
sn=sn/n1;

coeff=real(ifft((exp(1j*phase(fft(d))).*sp)./sn));
plot(coeff)
%%
fileID = fopen('Pattern.txt','w');
fprintf(fileID,'%12s\n',coeff);
fclose(fileID);
%%
f=0;
m=0;
count=1;
save=false;
for i=1:length(datap)
   if datap(i)>10
      save=true;
   end
   if save
       d(count)=datap(i-10);
       count=count+1;
       if count==2049
            count=1;
            save=false;
            f=f+d*coeff';
            m=m+1;
       end
   end
end
f=f/m;
fileID = fopen('Factor.txt','w');
fprintf(fileID,'%12s\n',f);
fclose(fileID);