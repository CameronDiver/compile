require 'term/ansicolor'
include Term::ANSIColor

$results = []

if ARGV.length < 1
	exit 1
end
$exe = ARGV[0]

def runDir dir
	entries = Dir[dir+"/*"]

	entries.each do |e|
		if File.directory? e
			runDir e
		elsif File.extname(e) == ".f"
			# run the parser on the file, and check
			# the return value. If it failed then report it
			str = "#{$exe} #{e} 1>/dev/null"
			if system str
				$results << [e, true]
			else
				$results << [e, false]
			end
		end
	end

end

runDir "."

passed = true

$results.each do |res|
	if res[1]
		resStr = green{ bold{ "#{res[1]}" } }
	else
		resStr = red{ bold { "#{res[1]}" } }
		passed = false
	end
	print bold { res[0] }, " : ", resStr, "\n"
end

if passed
	exit 0
else
	exit 1
end
