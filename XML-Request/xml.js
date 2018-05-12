var fs = require('fs');
var request = require('request');
var xml2js = require('xml2js');
var parser = xml2js.Parser();
var xmlj, xsdD, xsd, xml, xml1, xmlD, dom;

// Vinicius - "http://ruralruby.dlinkddns.com:8011" = Get
// Matheus - "http://tebd.000webhostapp.com" = Get/Post

var urlServerRaf = "http://10.10.4.128:8011";
var urlServerMatA = "http://10.10.8.87:8080";
var urlServerVin = "http://10.10.6.156:8011";

//require('request-debug')(request);
/*
0 - Sucesso
1 - XML inválido
2 - XML mal-formado
3 - Erro Interno
*/

/*
0 - Candidato não encontrado 
1 - Em processamento
2 - Candidato Aprovado e Selecionado
3 - Candidato Aprovado e em Espera
4 - Candidato Não Aprovado
*/

function submeter(xml) {
    request({
        headers: {
            'Content-Type': 'text/xml'
        },
        uri: urlServerRaf,
        body: xml.toString(),
        method: 'POST'
    }, function(err, res, body) {
        if (err) {
            return console.error('Submeter -> Erro', err);
        }
        console.log('Submeter -> sucesso!');
        console.log(body);
        parser.parseString(body, function(err, result) {
            xmlr = JSON.stringify(result);
            var sw = result.methodReturn.value[0];
            switch (sw) {
                case '0':
                    console.log("Sucesso");
                    break;
                case '-1':
                    console.log("XML inválido");
                    break;
                case '1':
                    console.log("XML inválido");
                    break;
                case '-2':
                    console.log("XML mal-formado");
                    break;
                case '2':
                    console.log("XML mal-formado");
                    break;
                case '3':
                    console.log("Erro Interno");
                    break;
            }
        });
    });
}

function consultarStatus(xml) {
    request({
        headers: {
            'Content-Type': 'text/xml'
        },
        uri: urlServerRaf, //+'?='+xml.toString(),
        body: xml.toString(),
        method: 'GET'
    }, function(err, res, body) {
        if (err) {
            return console.error('Consultar -> Erro', err);
        }
        console.log('Consultar -> sucesso!');
        console.log(body);
        parser.parseString(body, function(err, result) {
            xmlr = JSON.stringify(result);
            var sw = result.methodReturn.value[0];
            switch (sw) {
                case '0':
                    console.log("Candidato não encontrado");
                    break;
                case '1':
                    console.log("Em processamento");
                    break;
                case '2':
                    console.log("Candidato Aprovado e Selecionado");
                    break;
                case '3':
                    console.log("Candidato Aprovado e em Espera");
                    break;
                case '4':
                    console.log("Candidato Não Aprovado");
                    break;
            }
        });
    });
}

function main(nomeArquivo, funcao) {
    fs.readFile(__dirname + '/xmls/' + nomeArquivo, 'utf-8', function(err, buf) {
        if (err) { console.log("Arquivo não encontrado!"); return; }
        switch (funcao) {
            case 1:
                submeter(buf);
                break;
            case 2:
                consultarStatus(buf);
                break;
        }
        return true;
    });
}
var result = main('consultarStatus1.xml', 2);
var result2 = main('submeter0.xml', 1);