int printString | int a |
	if a - 10
		putchar(a + 97)
		printString(a + 1)
	else
		putchar(122)
	end

end


int main | |
	printString(0)
end