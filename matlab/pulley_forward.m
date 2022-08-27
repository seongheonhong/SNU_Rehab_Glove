r_0 = 5E-3;
z_0 = 1E-3;
C_0 = 0.5E-3;
tau_0 = 1.0;
s_0 = -(r_0+C_0+z_0)^2/(2*C_0);


s = 0:0.001:0.1;
F = tau_0./(sqrt(2*C_0*(s-s_0)) - C_0 - z_0);

figure(2);
plot(s, F);
% t_end = 4 * pi;
% t = t_0:0.001:t_end;
% val = t * 0;
% fun = @(s) C_0 * tau_0 ./ ((sqrt(2*C_0*s) - C_0 -z_0).^2 .* sqrt(2*C_0*s));
% 
% for i = 1 : size(t, 1)
%     val(i) = integral(fun, t_0, t(i));
% end