% declare variables
syms M m;
syms R g;

% define w
w = [(g./(2.*R)).^(1./2), (g.*(m+M)./(M.*R)).^(1./2)];

for i = 1:length(w)
    wi = w(i);
    
    % implement matrices
    Mat = m.*R.^2.*[2.*M./m + 1, 1; 1, 1];
    K = g.*R.*[m + M, 0; 0, m];
    full_mat = wi.^2.*Mat - K;

    % find nullspace of matrix
    x1 = null(full_mat);
    
    % make first element 1
    inv_first = x1(1)^(-1);
    x1 = inv_first.*x1;
    disp(x1)
end