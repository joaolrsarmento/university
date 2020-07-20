A = [1 5 6; 2 -5 8; 0 2 7];
lambda = leverrier(A);
fprintf("Autovalor dominante = %.8f\n", max(lambda));
% funcao para calcular os autovalores
function C = leverrier(A)
    a = size(A, 1);
    M = zeros(a);
    C = zeros(1, a + 1);
    C(1, 1) = 1;
    for k = 2:a + 1
        M = A * M + C(1, k-1) * eye(a);
        C(1, k) = -1/(k-1) * trace(A*M);
    end % C armazena os coef do polinomio caracteristico
    C = roots(C); % calculo dos autovalores
end


