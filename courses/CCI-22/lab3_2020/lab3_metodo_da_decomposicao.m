A=[3 -0.1 -0.2; 0.1 7 -0.3; 0.3 -0.2 10]; b=[7.85; -19.3; 71.4];
x = lu_sempivoteamento(A, b);
fprintf("O resultado encontrado:"); display(x);
function [x] = lu_sempivoteamento(A, b)
    n = size(A, 1); 
    L = eye(n); 
    for k = 1 : n
        L(k + 1 : n, k) = A(k + 1 : n, k) / A(k, k);
        for l = k + 1 : n
            A(l, :) = A(l, :) - L(l, k) * A(k, :);
        end
    end
    U = A;
    y = L\b;
    x = U\y;
end