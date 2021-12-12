var oldDomScoreboard = document.getElementsByClassName("scoreboard")[0].innerHTML; 

var official_values = [ "Nha Trang University", "University of Technology and Education-The University of Danang", "Naval Academy", "Da Nang University of Education", "Duy Tan University", "Hongduc University", "University of Science and Technology – The University of Danang", "Vietnam-Korea University of Information and Communication Technology, The University of Danang", "Hue University of Science","FPT University.","TeleCommunications University"];

function render_show_official() {
    if (showOfficial) {
        let official_filtered_rows = [];
        let scoreboard = 
document.getElementsByClassName("scoreboard")[0];
        let scoreboardRows = scoreboard.getElementsByTagName("tr");
        // Official rank idx iterates through the rows
        let j = 0;
        // Process the header row
        let headerRow = scoreboardRows[0];
        let officialRankHeaderTd = document.createElement("td");
        officialRankHeaderTd.innerText = "OR";
        officialRankHeaderTd.style.textAlign = "center";
        officialRankHeaderTd.style.fontWeight = "bold";
        headerRow.insertBefore(officialRankHeaderTd, 
headerRow.children[0]);
        for (let i = 0; i < scoreboardRows.length; i++) {
            let scoreboardRow = scoreboardRows[i];
            let scoretnTd = 
scoreboardRow.getElementsByClassName("scoretn")[0];
            if (!scoretnTd) continue;
            let spans = scoretnTd.getElementsByTagName("span")
            if (spans && spans.length > 0) {
                let span = spans[0];
                if (official_values.includes(span.innerText)) {
                    let officialValue = ++j;
                    let officialTd = document.createElement("td");
                    officialTd.innerText = officialValue;
                    officialTd.classList.add("official_rank");
                    
                    scoreboardRow.insertBefore(officialTd, 
scoreboardRow.children[0]);
                    official_filtered_rows.push(scoreboardRow.outerHTML);
                }
            }
        }
        let resultDom = official_filtered_rows.join("");
        // Embed the result in the page
        scoreboard.getElementsByTagName("tbody")[0].innerHTML = 
resultDom;
        // Tbody2 is summary
        let scoresummaryTr = document.getElementById("scoresummary")
        let officialRankTd = document.createElement("td");
        officialRankTd.innerText = official_filtered_rows.length;
        
        scoresummaryTr.insertBefore(officialRankTd, 
scoresummaryTr.children[0]);
    }
}
function init_show_official_ui() {
    // Create a checkbox to show official
    let showOfficialCheckbox = document.createElement("input");
    showOfficialCheckbox.type = "checkbox";
    showOfficialCheckbox.id = "show_official";
    showOfficialCheckbox.addEventListener("change", function () {
        showOfficial = showOfficialCheckbox.checked;
        if (showOfficial) {
            render_show_official();
        } else {
            document.getElementsByClassName("scoreboard")[0].innerHTML = 
oldDomScoreboard;
        }
    });
    // Create a label for the checkbox
    let showOfficialLabel = document.createElement("label");
    showOfficialLabel.htmlFor = "show_official";
    showOfficialLabel.innerText = "Show Central Only";
    // Create a div to hold the checkbox and label
    let showOfficialDiv = document.createElement("div");
    showOfficialDiv.classList.add("show_official");
    showOfficialDiv.appendChild(showOfficialCheckbox);
    showOfficialDiv.appendChild(showOfficialLabel);
    showOfficialDiv.style.display = "flex";
    showOfficialDiv.style.alignSelf = "center";
    showOfficialDiv.style.marginLeft = "auto";
    // embed the div in the page
    let tableHeader = 
document.getElementsByClassName("table-header")[0];
    tableHeader.style.display = "flex";
    tableHeader.appendChild(showOfficialDiv);
}
init_show_official_ui();
