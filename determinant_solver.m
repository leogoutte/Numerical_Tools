% declare variables
syms M m;
syms R g;
syms w;

% implement matrices
Mat = m.*R.^2.*[2.*M./m + 1, 1; 1, 1];
K = g.*R.*[m + M, 0; 0, m];
full_mat = w.^2.*Mat - K;

% calculate determinant
det_mat = det(full_mat) == 0;

% solve for w
S = solve(det_mat, w);

% simplify and square
Simple_sol = simplify(S).^2;

disp(Simple_sol)

