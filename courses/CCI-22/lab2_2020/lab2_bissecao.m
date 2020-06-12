format long
f=@(x) 4*sin(x) - exp(x);
epsilon = 0.00001; a = 0; b = 1; max = 100; condition = 0;
Bisseccao(f, a, b, epsilon, max, condition);
function [r,i] = Bisseccao(f, a, b, epsilon, max, condition)
i = 0;
while i < max
    i = i + 1; 
    r = (a + b)/2;
    if abs(a-b) < epsilon
        r = (a + b)/2;
        condition = 1;
        break
    end
    if f(a) * f(r) > 0
        a = r;
    else
        b = r;
    end
end
if condition == 0
    fprintf("Raiz aproximada: %.12f obtido com %d iterações - critério de parada número de iterações\n", r, i);
end
if condition == 1
    fprintf("Raiz aproximada: %.12f obtido com %d iterações - critério de parada epsilon\n", r, i);
end
end
