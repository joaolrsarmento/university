format long
f=@(x) 4*sin(x) - exp(x);
epsilon1 = 0.00001; epsilon2 = 0.00001; a = 0; b = 1; max = 100; condition=0;
FalsaPosicao(f, a, b, epsilon1, epsilon2, max, condition);
function [r,i] = FalsaPosicao(f, a, b, epsilon1, epsilon2, max, condition)
i = 0;
while i < max
    i = i + 1;
    r = (a * f(b) - b * f(a))/(f(b) - f(a));
    PontoPonderado = f(r);
    if abs(a-b) < epsilon1
        condition = 1;
        break
    end
    if abs(PontoPonderado) < epsilon2
        condition = 2;
        break
    end
    if f(a) * f(r) > 0
        a = r;
    else
        b = r;
    end
end
if condition == 0
    fprintf("Raiz aproximada: %.12f obtida com %d iterações - critério de parada número de iterações\n", r, i);
end
if condition == 1
    fprintf("Raiz aproximada: %.12f obtida com %d iterações - critério de parada epsilon1\n", r, i);
end
if condition == 2
    fprintf("Raiz aproximada: %.12f obtida com %d iterações - critério de parada epsilon2\n", r, i);
end
end