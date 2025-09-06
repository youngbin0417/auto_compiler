import sys
import os

# Add the project root directory to the Python path
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from preprocessor.parser import parse_code
from model.repair_model import repair_code
from postprocessor.code_generator import generate_code
from grammar_error_detector import PL0GrammarErrorDetector

def main():
    if len(sys.argv) != 2:
        print("Usage: python main.py <user_code.pl0>")
        sys.exit(1)
    
    # Read user code
    user_code_path = sys.argv[1]
    with open(user_code_path, 'r') as f:
        user_code = f.read()
    
    # Detect grammar errors in the user code
    print("Analyzing code for grammar errors...")
    detector = PL0GrammarErrorDetector()
    errors = detector.analyze(user_code)
    
    if errors:
        print(f"Found {len(errors)} potential grammar error(s):")
        for error in errors:
            print(f"Line {error['line']}: {error['type']} - {error['message']}")
        print("\nAttempting to repair code...\n")
    else:
        print("No obvious grammar errors detected.\n")
    
    # Parse the user code
    parsed_code = parse_code(user_code)
    
    # Repair the code using our model
    repaired_code = repair_code(parsed_code)
    
    # Generate the final code
    final_code = generate_code(repaired_code)
    
    # Output the repaired code
    print("Repaired code:")
    print(final_code)

if __name__ == "__main__":
    main()