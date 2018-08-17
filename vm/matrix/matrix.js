var char_set = [
    // 0 - 63
    "  ", "ア", "イ", "ウ", "エ", "オ", "カ", "ガ",
    "キ", "ギ", "ク", "グ", "ケ", "ゲ", "コ", "ゴ",
    "サ", "ザ", "シ", "ジ", "ス", "ズ", "セ", "ゼ",
    "ソ", "ゾ", "タ", "ダ", "チ", "ヂ", "ツ", "ヅ",
    "テ", "デ", "ト", "ド", "ナ", "ニ", "ヌ", "ネ",
    "ノ", "ハ", "バ", "ヒ", "ビ", "フ", "ブ", "ヘ",
    "ベ", "ホ", "ボ", "マ", "ミ", "ム", "メ", "モ",
    "ヤ", "ユ", "ヨ", "ラ", "リ", "ル", "レ", "ロ",
    // 64 - 127
    "ㄅ", "ㄆ", "ㄇ", "ㄈ", "ㄉ", "ㄊ", "ㄋ", "ㄌ",
    "ㄍ", "ㄎ", "ㄏ", "ㄐ", "ㄑ", "ㄒ", "ㄓ", "ㄔ",
    "ㄕ", "ㄖ", "ㄗ", "ㄘ", "ㄙ", "ㄚ", "ㄛ", "ㄜ",
    "ㄝ", "ㄞ", "ㄟ", "ㄠ", "ㄡ", "ㄢ", "ㄣ", "ㄤ",
    "ㄥ", "ㄦ", "ㄧ", "ㄨ", "ㄩ", "ㄪ", "ㄫ", "ㄬ",
    "ㆠ", "ㆡ", "ㆢ", "ㆣ", "ㆤ", "ㆥ", "ㆦ", "ㆧ",
    "ㆨ", "ㆩ", "ㆪ", "ㆫ", "ㆬ", "ㆭ", "ㆮ", "ㆯ",
    "ㆰ", "ㆱ", "ㆲ", "ㆳ", "ㆴ", "ㆵ", "ㆶ", "ㆷ",
    // 128 - 191 
    "⼀", "⼁", "⼂", "⼃", "⼄", "⼅", "⼆", "⼇",
    "⼈", "⼉", "⼊", "⼋", "⼌", "⼍", "⼎", "⼏",
    "⼐", "⼑", "⼒", "⼓", "⼔", "⼕", "⼖", "⼗",
    "⼘", "⼙", "⼚", "⼛", "⼜", "⼝", "⼞", "⼟",
    "⼠", "⼡", "⼢", "⼣", "⼤", "⼥", "⼦", "⼧",
    "⼨", "⼩", "⼪", "⼫", "⼬", "⼭", "⼮", "⼯",
    "⼰", "⼱", "⼲", "⼳", "⼴", "⼵", "⼶", "⼷",
    "⼸", "⼹", "⼺", "⼻", "⼼", "⼽", "⼾", "⼿",
    // 192 - 255
    "⺀", "⺁", "⺂", "⺃", "⺄", "⺅", "⺆", "⺇",
    "⺈", "⺉", "⺊", "⺋", "⺌", "⺍", "⺎", "⺏",
    "⺐", "⺑", "⺒", "⺓", "⺔", "⺕", "⺖", "⺗",
    "⺘", "⺙", "⺛", "⺜", "⺝", "⺞", "⺟", "⺠",
    "⺡", "⺢", "⺣", "⺤", "⺥", "⺦", "⺧", "⺨",
    "⺩", "⺪", "⺫", "⺬", "⺭", "⺮", "⺯", "⺰",
    "⺱", "⺲", "⺳", "⺴", "⺵", "⺶", "⺷", "⺸",
    "⺹", "⺺", "⺻", "⺼", "⺽", "⺾", "⺿", "⻀"
];

var op_names = [
    " ", "> live", "> ld", "> st", "> add", "> sub", "> and",
    "> or", "> xor", "> zjmp", "> ldi", "> sti", ">fork", 
    "> lld", "> lldi", "> lfork", "> aff"
]

var i = 0;
var players = champs.length;
var d;
var f;
var ops_line_nr = 3;
var c;
var speed = 1;

function cursorFlash(lnr)
{
    var lnr_prev = lnr - 1;
    if (lnr > 0)
    {
        clearInterval(d);
        $("#cursor_block"+lnr_prev).css("background-color", "black");
        $("#cursor_block"+lnr_prev).css("display", "none");
    }
    d = setInterval(cursorLight, 600);
    function cursorLight()
    {
        $("#cursor_block"+lnr).fadeIn(100).delay(800).fadeOut(100);
    }
}

function setScene()
{
    var j = 4032;
    var k = 4032;
    var left = 0;
    var topvalue = 0;

    while (i < 4096)
    {
        $("#container").append("<div class=\"char\" id=\"char"+j+"\"> </div>");
        $("#char"+j).css("left", left+"px");
        $("#char"+j).css("top", topvalue+"px");
        left = left + 26;
        i++;
        j -= 64;
        if (i % 64 == 0)
        {
            left = 0;
            topvalue = topvalue + 21;
            j = k + 1;
            k = j;
        }
    }
};

setScene();
i = 0;

function setBox()
{
    var j = 0;

    while (j < 5)
    {
        $("#status_box").append("<div class=\"linebox\" id=\"line"+j+"\"><div class=\"innerline\" id=\"innerline"+j+"\"></div></div>");
        if (j < 3)
            $("#ops_list_box").append("<div class=\"ops_linebox\" id=\"ops_line"+j+"\">></div>");
        j++;
    }
}

setBox();

function writeLine(str, lnr)
{
    var i = 0;
    $("#line"+lnr).html("");
    $("#line"+lnr).append("<div class=\"innerline\" id=\"innerline"+lnr+"\"></div>");
    $("#line"+lnr).append("<div id=\"cursor_block"+lnr+"\" class=\"cursor_block\"> </div>");
    cursorFlash(lnr);
    var e = setInterval(writeLetter, 2);
    function writeLetter()
    {
        $("#innerline"+lnr).append(str[i]);
        i++;
        if (i == str.length)
            clearInterval(e);
    }
}

lnr = 0;
writeLine("simulation status:", 0);

function firstOpen(callback)
{
    restartLoad();

    function pauseLoad()
    {   
        clearInterval(c);
        window.removeEventListener("keypress", pauseLoad);
        window.addEventListener("keypress", restartLoad);
        writeLine("loading paused...", 1);
    }

    function restartLoad()
    {
        window.removeEventListener("keypress", restartLoad);
        window.addEventListener("keypress", pauseLoad);
        c = setInterval(loadChamp, 0);
        writeLine("loading programs...", 1);
    }

    function loadChamp()
    {
        var j;
        var k;
        var byte = memory[0][1][i];
        var l = 0;
        if (byte >= 1000)
            byte = byte % 1000;
        if (i > 0)
        {
            k = i - 1;
            $("#char"+k).css("background-color", "black");
        }

        if (byte)
            $("#char"+i).css("background-color", "lightgreen");
        document.getElementById("char"+i).innerHTML = char_set[byte];
        if (players == 2)
        {
            byte = memory[0][1][i + 2047];
            if (byte >= 1000)
                byte = byte % 1000;
            j = i + 2047;
            k = j - 1;
            $("#char"+k).css("background-color", "black");
            if (byte)
                $("#char"+j).css("background-color", "lightgreen");
            document.getElementById("char"+j).innerHTML = char_set[byte];
        }
        if (players == 3)
        {   while (l < 2)
            {
                byte = memory[0][1][i + (l + 1) * 1365];
                if (byte >= 1000)
                    byte = byte % 1000;
                j = i + ((l + 1) * 1365);
                k = j - 1;
                $("#char"+k).css("background-color", "black");
                if (byte)
                    $("#char"+j).css("background-color", "lightgreen");
             document.getElementById("char"+j).innerHTML = char_set[byte];
             l++;
            }
        }
        if (players == 4)
        {   while (l < 3)
            {
                byte = memory[0][1][i + (l + 1) * 1024];
                if (byte >= 1000)
                    byte = byte % 1000;
                j = i + ((l + 1) * 1024);
                k = j - 1;
                $("#char"+k).css("background-color", "black");
                if (byte)
                    $("#char"+j).css("background-color", "lightgreen");
             document.getElementById("char"+j).innerHTML = char_set[byte];
             l++;
            }
        }
        i++;
        if (i == 683)
        {
            clearInterval(c);
            window.removeEventListener("keypress", pauseLoad);
            callback();
        }
    }
};

firstOpen(showGame);

 
function showGame()
{
    i = 0;
    while (i < players)
    {
        document.getElementById("player_profile"+i).innerHTML = char_set[champs[i][1]];
        document.getElementById("player_name"+i).innerHTML = champs[i][0];
        i++;
    }
    i = 0;
    var a;
    
    restartGame();

    function memoryDiff(i)
    {
        var l = 0;
        if (!i)
            return (0);
        while (l < 4096)
        {
            if (memory[i - 1][1][l] != memory[i][1][l])
                return (0);
            l++;
        }
        return (1);
    }

    function pauseGame()
    {
        clearInterval(a);
        window.removeEventListener("keypress", pauseGame);
        window.addEventListener("keypress", restartGame);
        writeLine("simulation paused...", 2);
    }

    function restartGame()
    {
        window.removeEventListener("keypress", restartGame);
        window.addEventListener("keypress", pauseGame);
        a = setInterval(setMatrix, 0);
        writeLine("executing simulation...", 2);
    }

    function setMatrix()
    {
        var byte;
        var l = 0;
        var p = 0;
        var j = 0;
        var k = 1;
        var m = 0;
        //
        window.onkeydown = checkKey;
        function checkKey(e) {
            e = e || window.event;
            if (e.keyCode == '38' && speed < 8 && speed >= 1)
            {
                speed++;
                $("#speed"+speed).css("opacity", "1");
                document.getElementById("speed_data").innerHTML = (speed * 12.5)+"%";
            }
            else if (e.keyCode == '40' && speed <= 8 && speed > 1)
            {
                $("#speed"+speed).css("opacity", "0.5");
                speed--;
                document.getElementById("speed_data").innerHTML = (speed * 12.5)+"%";
            }
        }
        //
        document.getElementById("cycle").innerHTML = i + 1;
        while (k < 17)
        {
            $("#op_c"+k).css("background-color", "black");
            k++;
        }
        while (i > 0 && l < memory[i][0].length)
        {
            j = memory[i - 1][0][l];
            k = memory[i][0][l];
            if (k > 0 && k < 17)
            {
                $("#op_c"+k).css("background-color", "lightgreen");
            }
            if (i > 0 && memory[i][0][l] == 0 && j < 17 && j > 0)
            {
                m = ops_line_nr - 3;
                $("#ops_line"+m).css("display", "none");
                $("#ops_list_box").append("<div class=\"ops_linebox\" id=\"ops_line"+ops_line_nr+"\"></div>");
                $("#ops_line"+ops_line_nr).append(op_names[memory[i - 1][0][l]]);
                ops_line_nr++;
            }
            l++;
        }
        l = 0;
        while (l < 4096 && i < 6000 && !memoryDiff(i))
        {
            byte = memory[i][1][l];
            if (byte >= 1000)
            {
                $("#char"+l).css("background-color", "lightgreen");
                byte = byte % 1000;
                p++;
            }
            else
            {
                $("#char"+l).css("background-color", "black");
                $("#char"+l).css("color", "limegreen");
                $("#char"+l).css("font-weight", "normal");
            }
            if (i == 0 || memory[i - 1][1][l] != byte)
            {
                document.getElementById("char"+l).innerHTML = char_set[byte];
                $("#char"+l).css("color", "greenyellow");
                $("#char"+l).css("font-weight", "bold");
            }
            document.getElementById("processes").innerHTML = p;
            l++;
        }
        if (i + speed >= 6000)
            i++;
        else
            i = i + speed;
        if (i <= 0)
            i = 0;
        if (i >= 6000)
        {
            window.removeEventListener("keypress", pauseGame);
            clearInterval(a);
            $("#game_over").css("display", "block");
            writeLine("execution complete", 3);
            clearInterval(d);
        }
    }
}



// - make the flags
// - lives (21)?
// - cycles to die
// - winner champ
// - (cycle delta) 
// - (max checks)
// - (nbr live)
// - show 0 changes
