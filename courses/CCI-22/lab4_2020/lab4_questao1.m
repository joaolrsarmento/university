format long
X = [-7 -4 -2 1 2]; % X values
Y = [-1 -3 1 0 0.5]; % Y values

MatrizDeVandermonde(X,Y);
function MatrizDeVandermonde(X,Y)
    n = length(X); % Get length of the input
    A = zeros(n,n); % Initiate matrix A to speed up operations
    for i = 1:n
        for j = 1:n
            A(i,j) = X(i) ^ (j-1); % Get Vandermond's matrix, element by element
        end
    end
    B = Y'; % Transpose
    C = A \ B; % Get B.A^-1
    for i = 0:n-1
        fprintf("a%d = %.5f\n", i, C(i+1)); % Print coeficients
    end
end