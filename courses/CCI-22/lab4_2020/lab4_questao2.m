format long
X = [-1 0 2 5 6 9 10]; % Get x values
Y = [1 1 0 -1 -2 -5 -18]; % Get y values
DividedDifferences(X,Y);
function DividedDifferences(X,Y)
    n = length(X); % Get length of the input
    B = zeros(n,n); % Initiate matrix B to speed up operations
    B(:,1) = Y(:);
    for j = 2:n
        for i = 1:n-j+1
            B(i,j) = (B(i+1, j-1) - B(i, j-1))/(X(i+j-1)-X(i)); % Difference
        end
    end
    for i = 1:n
        fprintf("Ordem %d\n", i- 1); 
        for j = 1:n
            fprintf("%d\n", B(j,i)); % Print order i
        end
        n = n - 1; % Move to the previous element
    end
end