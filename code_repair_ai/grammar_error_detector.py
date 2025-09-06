#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
PL/0 Grammar Error Detector

This module analyzes PL/0 source code and detects common grammar errors
by parsing the code according to the PL/0 grammar rules defined in the yacc file.
"""

import re
import sys
from typing import List, Tuple, Dict, Any

class PL0GrammarErrorDetector:
    def __init__(self):
        # Define PL/0 grammar rules based on the yacc file
        self.keywords = {
            'const', 'var', 'procedure', 'call', 'begin', 'end', 
            'if', 'then', 'while', 'do', 'odd', 'write'
        }
        
        # Define expected patterns for different constructs
        self.patterns = {
            'const_decl': r'const\s+[a-zA-Z_][a-zA-Z0-9_]*\s*=\s*\d+',
            'var_decl': r'var\s+[a-zA-Z_][a-zA-Z0-9_]*(\s*,\s*[a-zA-Z_][a-zA-Z0-9_]*)*',
            'procedure_decl': r'procedure\s+[a-zA-Z_][a-zA-Z0-9_]*\s*;',
            'assignment': r'[a-zA-Z_][a-zA-Z0-9_]*\s*:=[^;]*',
            'call_stmt': r'call\s+[a-zA-Z_][a-zA-Z0-9_]*',
            'begin_end_block': r'begin\s+.*\s+end',
            'if_stmt': r'if\s+.*\s+then\s+.*',
            'while_stmt': r'while\s+.*\s+do\s+.*',
            'write_stmt': r'write\s+[a-zA-Z_][a-zA-Z0-9_]*'
        }
    
    def detect_missing_semicolon(self, lines: List[str]) -> List[Dict[str, Any]]:
        """Detect missing semicolons at the end of statements"""
        errors = []
        
        # Patterns that should typically end with semicolons
        statement_patterns = [
            r'const\s+[a-zA-Z_][a-zA-Z0-9_]*\s*=\s*\d+',  # const declarations
            r'var\s+[a-zA-Z_][a-zA-Z0-9_]*(\s*,\s*[a-zA-Z_][a-zA-Z0-9_]*)*',  # var declarations
            r'[a-zA-Z_][a-zA-Z0-9_]*\s*:=[^;]*',  # assignments
            r'call\s+[a-zA-Z_][a-zA-Z0-9_]*',  # procedure calls
        ]
        
        for i, line in enumerate(lines):
            # Check if line matches a statement pattern but doesn't end with semicolon
            for pattern in statement_patterns:
                if re.search(pattern, line) and not line.strip().endswith(';'):
                    # Make sure it's not a procedure declaration which doesn't need semicolon
                    if not re.match(r'procedure\s+[a-zA-Z_][a-zA-Z0-9_]*\s*;', line):
                        errors.append({
                            'line': i + 1,
                            'type': 'MISSING_SEMICOLON',
                            'message': f'Missing semicolon at end of statement'
                        })
                        break
        
        return errors
    
    def detect_unmatched_begin_end(self, lines: List[str]) -> List[Dict[str, Any]]:
        """Detect unmatched begin/end blocks"""
        errors = []
        begin_count = 0
        end_count = 0
        begin_lines = []
        
        for i, line in enumerate(lines):
            # Count begin and end keywords
            begin_matches = re.findall(r'\bbegin\b', line)
            end_matches = re.findall(r'\bend\b', line)
            
            begin_count += len(begin_matches)
            end_count += len(end_matches)
            
            # Track line numbers where 'begin' occurs
            for match in begin_matches:
                begin_lines.append(i + 1)
        
        # Check for unmatched blocks
        if begin_count > end_count:
            errors.append({
                'line': begin_lines[-1] if begin_lines else len(lines),
                'type': 'UNMATCHED_BEGIN',
                'message': f'Unmatched begin block. Found {begin_count} "begin" but {end_count} "end"'
            })
        elif end_count > begin_count:
            errors.append({
                'line': len(lines),
                'type': 'UNMATCHED_END',
                'message': f'Unmatched end block. Found {end_count} "end" but {begin_count} "begin"'
            })
        
        return errors
    
    def detect_invalid_identifiers(self, lines: List[str]) -> List[Dict[str, Any]]:
        """Detect identifiers that conflict with keywords"""
        errors = []
        
        for i, line in enumerate(lines):
            # Find all identifiers (words that are not numbers or keywords)
            words = re.findall(r'[a-zA-Z_][a-zA-Z0-9_]*', line)
            
            for word in words:
                # Check if word is a keyword being used as an identifier
                if word in self.keywords:
                    # Check if it's being used as an identifier (not as a keyword)
                    # This is a simple heuristic - in practice, we'd need more context
                    context_pattern = rf'(var|const)\s+{word}\b|{word}\s*:='
                    if re.search(context_pattern, line):
                        errors.append({
                            'line': i + 1,
                            'type': 'INVALID_IDENTIFIER',
                            'message': f'Using keyword "{word}" as identifier'
                        })
        
        return errors
    
    def detect_missing_declarations(self, lines: List[str]) -> List[Dict[str, Any]]:
        """Detect use of undeclared variables"""
        errors = []
        declared_vars = set()
        
        # First pass: collect declared variables
        for line in lines:
            # Match const declarations
            const_matches = re.findall(r'const\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=', line)
            declared_vars.update(const_matches)
            
            # Match var declarations
            var_match = re.search(r'var\s+([a-zA-Z_][a-zA-Z0-9_,\s]*)', line)
            if var_match:
                var_list = var_match.group(1).split(',')
                for var in var_list:
                    declared_vars.add(var.strip())
        
        # Second pass: check for undeclared variables in assignments and expressions
        for i, line in enumerate(lines):
            # Skip declaration lines
            if re.match(r'(const|var)\s+', line):
                continue
                
            # Find variables being used (in assignments, expressions, etc.)
            # This is a simplified pattern - a full parser would be more accurate
            var_uses = re.findall(r'([a-zA-Z_][a-zA-Z0-9_]*)\s*:=[^;]*|[+\-*/()=\s]([a-zA-Z_][a-zA-Z0-9_]*)[+\-*/()=\s;]', line)
            
            for var_use in var_uses:
                # var_use is a tuple, we need to check both elements
                for var in var_use:
                    if var and var not in self.keywords and var not in declared_vars and not var.isdigit():
                        # Simple check - in a real implementation, we'd need to be more precise
                        # about determining if this is actually a variable use
                        if len(var) > 1 or (len(var) == 1 and var.isalpha()):
                            errors.append({
                                'line': i + 1,
                                'type': 'UNDECLARED_VARIABLE',
                                'message': f'Use of undeclared variable "{var}"'
                            })
        
        return errors
    
    def analyze(self, source_code: str) -> List[Dict[str, Any]]:
        """
        Analyze PL/0 source code and return a list of detected grammar errors.
        
        Args:
            source_code: PL/0 source code as a string
            
        Returns:
            List of error dictionaries with line number, error type, and message
        """
        lines = source_code.split('\n')
        errors = []
        
        # Run all detection methods
        errors.extend(self.detect_missing_semicolon(lines))
        errors.extend(self.detect_unmatched_begin_end(lines))
        errors.extend(self.detect_invalid_identifiers(lines))
        # Note: Missing declarations detection is complex and might produce false positives
        # errors.extend(self.detect_missing_declarations(lines))
        
        # Sort errors by line number
        errors.sort(key=lambda x: x['line'])
        
        return errors

def main():
    if len(sys.argv) != 2:
        print("Usage: python grammar_error_detector.py <pl0_source_file>")
        sys.exit(1)
    
    try:
        with open(sys.argv[1], 'r') as f:
            source_code = f.read()
        
        detector = PL0GrammarErrorDetector()
        errors = detector.analyze(source_code)
        
        if errors:
            print(f"Found {len(errors)} potential grammar error(s):")
            for error in errors:
                print(f"Line {error['line']}: {error['type']} - {error['message']}")
        else:
            print("No obvious grammar errors detected.")
            
    except FileNotFoundError:
        print(f"Error: File '{sys.argv[1]}' not found.")
        sys.exit(1)
    except Exception as e:
        print(f"Error analyzing file: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()