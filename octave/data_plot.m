data = load('E:/tools/showtool&NavigationAnalysis/extract2.txt');

scci_ax = data(:,1);
scci_ay = data(:,2);
scci_az = data(:,3);

wx = data(:,4);
wy = data(:,5);
wz = data(:,6);

bmi_ax = data(:,7);
bmi_ay = data(:,8);
bmi_az = data(:,9);

tmperature = data(:, 10);

%plot(scci_ax, ";scci_ax;", scci_ay, ";scci_ay;", scci_az, ";scci_az;", wx, ";wx;", wy, ";wy;", wz, ";wz;");
%plot(scci_ax, ";scci_ax;", scci_ay, ";scci_ay;", scci_az, ";scci_az;", tmperature, ";temperature;");
plot(bmi_ax, ";bmi\_ax;", bmi_ay, ";bmi\_ay;", bmi_az, ";bmi\_az;", scci_ax,
";scci\_ax;", scci_ay, ";scci\_ay;", scci_az, ";scci\_az;",
tmperature, ";temperature;");
%plot(wx, ";wx;", wy, ";wy;", wz, ";wz;")

%plot(ax, ";ax;", ay, ";ay;", az, ";az;", wx, ";wx;", wy, ";wy;", wz, ";wz;")
%plot(az, ";az;", wz, ";wz;")
%plot( az, ";az;")
%plot(wx, ";wx;", wy, ";wy;", wz, ";wz;")