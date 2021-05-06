
import js2py

f = js2py.eval_js( "function $(name) {return name.length}" )

print(f("Hello world"))

# returns 11
