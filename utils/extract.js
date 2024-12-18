// Function to extract telegraph codes
function extractTelegraphCodes() {
  const result = []; // Array to hold extracted codes
  
  // Select all rows with the class 'result-tr'
  const rows = document.querySelectorAll('tr.result-tr');
  
  rows.forEach(row => {
    // For each row, find the <td> elements with the class 'code'
    const code = row.querySelectorAll('td.code')[0];
    
    const codeText = code.textContent.trim();
    if (codeText && !codeText.startsWith('U+')) {
      // Exclude Unicode values and empty cells
      result.push(codeText);
    }
  });
  
  console.log(result); // Log the extracted codes to console
  return result; // Return the array of codes
}

// Call the function
telegraphCodes = extractTelegraphCodes();
console.log("Extracted Telegraph Codes:", telegraphCodes);
// Function to extract telegraph codes
function extractTelegraphCodes() {
  const result = []; // Array to hold extracted codes
  
  // Select all rows with the class 'result-tr'
  const rows = document.querySelectorAll('tr.result-tr');
  
  rows.forEach(row => {
    // For each row, find the <td> elements with the class 'code'
    const code = row.querySelectorAll('td.code')[0];
    
    const codeText = code.textContent.trim();
    if (codeText && !codeText.startsWith('U+')) {
      // Exclude Unicode values and empty cells
      result.push(codeText);
    }
  });
  
  console.log(result); // Log the extracted codes to console
  return result; // Return the array of codes
}

// Call the function
telegraphCodes = extractTelegraphCodes();
console.log("Extracted Telegraph Codes:", telegraphCodes);
