clear all; %#ok<CLALL>
clc;
close all;

load ../testCase/Mesh/CX.txt
load ../testCase/Mesh/CY.txt


% load ../testCase/0/mu.txt
% load ../testCase/0/rho.txt
% load ../testCase/0/UX.txt
% load ../testCase/0/UY.txt
% load ../testCase/0/UZ.txt
% load ../testCase/0/p.txt
% load ../testCase/0/divphiU.txt


load ../testCase/1/mu.txt
load ../testCase/1/rho.txt
load ../testCase/1/UX.txt
load ../testCase/1/UY.txt
load ../testCase/1/UZ.txt
load ../testCase/1/p.txt
load ../testCase/1/divphiU.txt


% load ../testCase/10/mu.txt
% load ../testCase/10/rho.txt
% load ../testCase/10/UX.txt
% load ../testCase/10/UY.txt
% load ../testCase/10/UZ.txt
% load ../testCase/10/p.txt
% load ../testCase/10/divphiU.txt

% load ../testCase/30/mu.txt
% load ../testCase/30/rho.txt
% load ../testCase/30/UX.txt
% load ../testCase/30/UY.txt
% load ../testCase/30/UZ.txt
% load ../testCase/30/p.txt
% load ../testCase/30/divphiU.txt
% % 
% 
% load ../testCase/50/mu.txt
% load ../testCase/50/rho.txt
% load ../testCase/50/UX.txt
% load ../testCase/50/UY.txt
% load ../testCase/50/UZ.txt
% load ../testCase/50/p.txt
% load ../testCase/50/divphiU.txt



load ../testCase/100/mu.txt
load ../testCase/100/rho.txt
load ../testCase/100/UX.txt
load ../testCase/100/UY.txt
load ../testCase/100/UZ.txt
load ../testCase/100/p.txt
load ../testCase/100/divphiU.txt

load ../testCase/500/mu.txt
load ../testCase/500/rho.txt
load ../testCase/500/UX.txt
load ../testCase/500/UY.txt
load ../testCase/500/UZ.txt
load ../testCase/500/p.txt
load ../testCase/500/divphiU.txt

load ../testCase/2000/mu.txt
load ../testCase/2000/rho.txt
load ../testCase/2000/UX.txt
load ../testCase/2000/UY.txt
load ../testCase/2000/UZ.txt
load ../testCase/2000/p.txt
load ../testCase/2000/divphiU.txt


% load ../testCase/5000/mu.txt
% load ../testCase/5000/rho.txt
% load ../testCase/5000/UX.txt
% load ../testCase/5000/UY.txt
% load ../testCase/5000/UZ.txt
% load ../testCase/5000/p.txt
% load ../testCase/5000/divphiU.txt


figure(1)
[~,h] =contourf(CX,CY,UX,25);
hcb=colorbar;
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$U_x-Velocity$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure1.png')


figure(2)
[~,h] =contourf(CX,CY,UY,25);
colorbar
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$U_y-Velocity$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure2.png')


figure(3)
[~,h] =contourf(CX,CY,UZ,25);
colorbar
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$U_z-Velocity$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure3.png')

figure(4)
[~,h] =contourf(CX,CY,p,25);
colorbar
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$Pressure$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure4.png')


figure(5)
[~,h] =contourf(CX,CY,divphiU,25);
colorbar
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$Divergence$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure5.png')

figure(6)
surf(CX,CY,UX);
hcb=colorbar;
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$U_x-Velocity$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure6.png')
