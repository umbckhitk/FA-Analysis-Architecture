# FA-Analysis-Architecture

## Initial architecture (based on the dicussion)
<img width="214" alt="initial soc arch" src="https://github.com/user-attachments/assets/9abc45c7-f293-4ef2-ad29-3e1892cc2b78" /><br> <br>
<p> After talking with the team over the interview the <strong> panel was very intrested on the architecture that I proposed </strong>. It was hard for me to explain it over the interview but the panel was super happy about my suggestion <br><br>
 This is the understanding of entire architecute of the test plan. I felt there was enough room for improvement and using automation pipelines for continous code build and continous code deploy. <br><br>
The idea is to have AI intervining the triage process and analystic process <br><br>
Most of the trigae of the test cases can be divided into 3 catagories of failure ,<br><br>
  <ol>
<li>system/firmware failure </li>
<li>setup failure </li>
<li>test failure </li>
  </ol> <br>
### My analysis during interview. <br>

These failures are addreses by manually viewing the failures and triaging them based on the their failures. the enhancement is to eliminate the manual failure analysis to up to <strong>70 % </strong> and also improve the effenciey. <br>
the other proposed architecutre was to give the user the ability to <strong> compare exisitng test run vs the latest bench mark result of previous test history </strong> for the same test with different/same gpu or soc model. </p> <br>
<strong> Log file analysis </strong> by the model is also a feature that can be drivin in order to have the clear understandig of error pinpoints and initial point of failure for the system. and identifying the point of failure <br><br>

## Proposed/Intrested architecture <br><br>

<img width="598" alt="proposed_architecture_of_FA" src="https://github.com/user-attachments/assets/d31b32a4-02ef-422b-ba79-d72e86f62cf1" /> <br>
<br>
All the tests are based on TTD - test driven development Document, testing requirements based on the SoC's intended use cases, performance metrics, and reliability standards.
<br><br>
The architecture is designed to automate the process of testing and analyzing the performance of devices (DUT-1 and DUT-2 and so on ). It starts with automated tests running on the devices, generating test result files (pass or fail). These results are then fed into a central system where they are stored and analyzed. If any failures are detected, such as setup errors or firmware issues, the test suite is updated to address these issues, and bugs are logged. The results from the current device (DUT) are compared to a benchmark device, and a failure analysis dashboard is used to visualize metrics such as pass/fail rates, error types, and test durations. This helps in improving future tests by identifying trends and potential improvements in the testing process.<br>



