const button = document.querySelector("#button")
button.addEventListener("click",function(){
    document.querySelector("nav").classList.toggle("dark");
    document.querySelectorAll("a").forEach(function(a){
        a.classList.toggle("dark");
    });
    document.querySelectorAll("span").forEach(function(span){
        span.classList.toggle("dark");
    });
    document.querySelectorAll("div").forEach(function(div){
        div.classList.toggle("dark");
    });
    document.querySelectorAll("li").forEach(function(li){
        li.classList.toggle("dark");
    });
    document.querySelector("body").classList.toggle("dark")
//     document.querySelector("nav").classList.toggle("dark")
});