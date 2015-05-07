extern int printNum | int a |

int mod | int a, int b |
	while a >= b
		a = a - b
	end
	a
end

int main ||
	int prime = 1
	while prime < 100000
		int divisor = prime - 1
		int isprime = 1
		while divisor > 1
			if mod(prime, divisor) == 0
				
			else
				isprime = 0
				divisor = divisor - divisor + 1
			end
			divisor -= 1
		end

		if isprime
			printNum(prime)
		end
		prime += 1
	end
end