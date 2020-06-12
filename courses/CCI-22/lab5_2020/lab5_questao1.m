format long
f=@(x) 4 ./ (5 + 2 * x.^2); % Creating f function
initial_degree = 2; final_degree = 10; % P degree range
a = -3; b = 3; % Interpolation range
for n=initial_degree:final_degree
    xc=cos(pi*(0:n)/n); 
    x=(a+b)*0.5 - (b-a)*0.5*xc; % Creating Chebyschev's nodes
    fprintf('\np degree = %d\n', n);
    for i=1:n+1
        fprintf('x%d = %.5f\n',i-1, x(1, i));
    end
    y = f(x); % Prepare for interpolation
    fit = polyfit(x, y, n);
    for i=1:n+1
        fprintf('p%d = %.5f\n', i-1, fit(1, i)); % Printing p coefficients
    end
    x = linspace(a, b, 100); p = polyval(fit, x); max_error = max(abs(f(x) - p)); % Calculation max error
    fprintf('Max error found = %.5f', max_error);
    results = [f(x); polyval(fit , x)]; % Store results for plotting 100 points
    % Plotting
    figure(n);
    title('Combined plot f and p'); plot(x, results);
    lgd = legend; lgd.FontSize = 12; lgd.Title.String = strcat('P degree=', num2str(n));
    legend('f(x)', 'p(x)');
end

