format long
f = @(x) x.^10 - 3 * x.^2 - 2; % f(x) function
X = linspace(-1, 0, 100); % Get X values from a equally space range
g = @(x) -1.004 * x.^2 + 0.996 * x - 2; % g(x) function
P = polyfit(X, f(X), 2); % Generate fit in a quadratic polynomial
p = @(x) P(1) * x.^2 + P(2) * x + P(3); % Create polynomial based on the coefficients
max_error_f_g = max(abs(f(X) - g(X))); % Get max error between f and g values
max_error_f_p = max(abs(f(X) - p(X))); % Get max error between f and p values

results = [f(X);g(X);p(X)]; % Store f, g and p values

fprintf("Maior erro entre f e g nos 100 pontos: %.16f\n", max_error_f_g);
fprintf("Maior erro entre f e p nos 100 pontos: %.16f\n", max_error_f_p);

plot(X, results); % Plot the result obtained
title("Gráficos obtidos");
legend("f(x)", "g(x)", "p(x)");
xlabel("x");