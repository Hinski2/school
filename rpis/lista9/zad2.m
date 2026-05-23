X = csvread('z0901.csv');
n = length(X);
x_mean = mean(X);
sigma = sqrt(8);

function d = dystrybuanta(x_mean, mi, sigma, n)
    z = (x_mean - mi) / (sigma / sqrt(n));
    d = 0.5 * (1 + erf(z / sqrt(2)));
end

% mi = 1.5
phi = dystrybuanta(x_mean, 1.5, sigma, n);
printf("mi = 1.5, phi(z) = %f\n", phi);

% mi = 1.75
phi = dystrybuanta(x_mean, 1.75, sigma, n);
printf("mi = 1.75, phi(z) = %f\n", phi);
