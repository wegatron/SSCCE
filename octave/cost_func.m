function J=cost_func(x, y, theta)
  m = length(y);
  cost = x * theta - y;
  J = sum(cost.^2)/m;
endfunction
