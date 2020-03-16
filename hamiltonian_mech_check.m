% declare variables
syms t;
syms x0 p0 m w;

% implement variables
r = sqrt(x.^2 + y.^2);
phi = atan(y./x);

x = x0.*cos(w.*t);
y = p0./(m.*w).*sin(w.*t);

l = x0.*p0;

% LHS
lhs = m.*diff(r,t,2);

% RHS
rhs = l.^2./(m.*r.^3) - m.*w.^2.*r;

% check
disp("This should be zero:");
disp(simplify(lhs - rhs))
