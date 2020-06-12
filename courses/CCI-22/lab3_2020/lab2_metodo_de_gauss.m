A=[3 -0.1 -0.2; 0.1 7 -0.3; 0.3 -0.2 10];
b=[7.85; -19.3; 71.4];
n=size(A,1);
x = EliminacaodeGauss(A, b, n);
fprintf("O resultado encontrado:");
display(x);
function x = EliminacaodeGauss(A, b, n)
    for k=1:n-1
        for i=k+1:n
            M = A(i,k)/A(k,k);
            A(i,k) = 0;
            for j=k+1:n
                A(i,j) = A(i,j) - M*A(k,j);
            end
            b(i,1) = b(i,1) - M*b(k,1);
        end
    end
    x(n,1)=b(n,1)/A(n,n);
    for k=n-1:-1:1
        S = 0;
        for j=k+1:n
            S = S + A(k,j)*x(j,1);
        end
        x(k,1) = (b(k,1)-S)/A(k,k);
    end
end