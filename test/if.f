int printString | int a |
	if a - 10
		if a - 5
			putchar(a + 97)
			printString(a + 1)
		else
			putchar(a + 41)
			printString(a + 1)
		end
		
	else
		putchar(122)
	end

end


int main | |
	printString(0)
end