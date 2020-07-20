A = [1 5 6; 2 -5 8; 0 2 7];
tolerances = [0.1 0.01 0.001 0.0001];
real = 8.56582869;
n = size(tolerances, 2);
for i=1:n % calculate for each value of tolerance 
    tol = tolerances(i);
    [lambda, k] = potencia(A, tol);
    erro = abs(lambda - real);
    fprintf('Epsilon = %.4f | Erro absoluto = %.8f |', tol, erro);
    fprintf('Autovalor dominante = %.8f | Numero de iteracoes = %d\n', lambda, k);
end

function [lambda, k] = potencia(A, tol)
    k = 0; kmax = 1000; erro = inf;
    n = size(A, 1); y0 = ones(n, 1);
    while erro > tol && k < kmax
        x = A * y0;
        [maximum, index] = max(abs(x(:)));
        lambda = maximum * sign(x(index));
        y = x/lambda;
        erro = max(abs(y-y0));
        y0 = y; k = k+1;
    end
end

