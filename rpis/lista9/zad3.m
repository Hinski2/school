pkg load statistics;

X = csvread('z0901.csv');
n = length(X);
x_mean = mean(X);

sigma = std(X);
function d = dystrybuanta(x_mean, mi, sigma, n)
    t = (x_mean - mi) / (sigma / sqrt(n));
    d = tcdf(t, n - 1);

end

% mi = 1.5
phi = dystrybuanta(x_mean, 1.5, sigma, n);
printf("P(X < 1.5) = %f\n", phi);

% mi = 1.75
phi = dystrybuanta(x_mean, 1.75, sigma, n);
printf("P(X < 1.75) = %f\n", phi);