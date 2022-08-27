clear; close all;
%% Set parameters
r0 = 7.5E-3;            % in [mm]
t0 = 0;                 % in [rad]
k = 100;                % in [N/m]
tau0 = 0.2;             % in [Nm]
z0 = 0.003;             % in [m/rad]

rspan = r0 * [1, 2.5];
[r, t] = ode45(@(r, t) fprime(r, t, k, tau0, z0), rspan, t0);
[p, S] = polyfit(t, r, 4);

figure();
plotstyle0;
plot(t,r,'ro');
plot(t, polyval(p,t), 'b-');
figure();
plotstyle0;
plot(0.003*t,r,'k-');
daspect([1, 1, 1]);


tspan = [t(1), t(size(t, 1))];
save('pulley_result.mat', 'p', 'tspan');

function dtdr = fprime(r, t, k, tau0, z0)        
    dtdr = ((tau0 ./ (k * r.^2)) - 1) ./ (r + z0);
end