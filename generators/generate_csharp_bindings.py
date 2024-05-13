import json
import sys  # Import sys to handle command line arguments

def generate_csharp_bindings(json_file, output_file):
    # Open and parse the JSON API description file
    with open(json_file, 'r') as file:
        api = json.load(file)

    with open(output_file, 'w') as out:
        # Generate a C# class file with necessary usings
        out.write("using System;\n")
        out.write("using System.Runtime.InteropServices;\n\n")

        # Namespace to contain all the bindings
        out.write("namespace GodotBindings {\n")

        # Loop through each class in the JSON
        for cls in api['classes']:
            # Define a class
            out.write(f"    public static class {cls['name']} {{\n")

            # Generate method bindings
            for method in cls['methods']:
                # Handle missing return_type safely
                return_type = method.get('return_type', 'void')  # Default to 'void' if not found

                # Form the method signature
                params = ', '.join([f"{arg['type']} {arg['name']}" for arg in method.get('arguments', [])])
                out.write(f"        [DllImport(\"libCONST_INT.linux.template_debug.x86_64.so\", CallingConvention = CallingConvention.Cdecl)]\n")
                out.write(f"        public static extern {return_type} {method['name']}({params});\n")

            # End of class
            out.write("    }\n\n")

        # End of namespace
        out.write("}")

def main():
    # Check if the correct number of arguments are passed
    if len(sys.argv) != 3:
        print("Usage: python generate_csharp_bindings.py <path_to_json_file> <path_to_output_file>")
        return

    # Path to the JSON file containing the API description
    json_file = sys.argv[1]
    # Output file for the C# bindings
    output_file = sys.argv[2]
    # Generate the bindings
    generate_csharp_bindings(json_file, output_file)
    print(f"C# bindings generated successfully in {output_file}")

if __name__ == "__main__":
    main()
