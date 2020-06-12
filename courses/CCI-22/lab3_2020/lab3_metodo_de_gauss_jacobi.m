format long
A=[3 -0.1 -0.2; 0.1 7 -0.3; 0.3 -0.2 10];b=[7.85; -19.3; 71.4];epsilon=0.0000001;
[X1, dr, k] = Gauss_Jacobi(A,b,epsilon);
fprintf("A solução do sistema foi obtida com %d iterações e %d de epsilon:", k, dr); display(X1);
function[X1, dr, k]= Gauss_Jacobi(A,b,epsilon)
    ord=size(A);
    X = zeros(size(b));
    for i=1:size(b)
        X(i,1)=b(i,1)/A(i,i);
    end
    k = 1; C = zeros(size(A)); g = zeros(size(b));
    for i = 1:ord
        for j = 1:ord
            if i == j
                C(i,j) = 0;
                g(i,1) = b(i,1)/A(i,i);
            else
                C(i,j) =-A(i,j)/A(i,i);
            end
        end
    end
    while true
        X1=C*X+g; deltax = zeros(size(b));
        for i = 1:ord
            deltax(i,1)=abs(X1(i,1)-X(i,1));
        end
        dr=max(abs(deltax))/max(abs(X1));
        if (dr<epsilon) 
            break;
        end
        X = X1; k = k+1;
    end
end