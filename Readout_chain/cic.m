yi=filter(1,[1 -1],data);
yi2=filter(1,[1 -1],yi);
yi3=filter(1,[1 -1],yi2);
datf=yi3(1:128:end);
datc=filter([1 -1],1,datf);
datc2=filter([1 -1],1,datc);
datc3=filter([1 -1],1,datc2);
figure
plot(datc3/max(datc3))
hold on
plot(data(1:128:end)/max(data(1:128:end)),'r')
figure
fs=20*10^6;
subplot(2,1,1)
f1=0:fs/(128*length(datc2)):fs/128-fs/(128*length(datc2));
semilogx(f1,20*log10(abs(fft(datc3/max(datc3)))))
subplot(2,1,2)
f2=0:fs/length(data):fs-fs/length(data);
semilogx(f2,20*log10(abs(fft(data/max(data)))))
