#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define endl "\n"
#define all(x) x.begin(), x.end()
#define pb push_back

string treat_string(string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

string concat(vector<string> vs){
    string aux = "";
    for(int i=0; i<vs.size(); i++){
        aux += vs[i];
        if(i != vs.size()-1) aux += " ";
    }
    return aux;
}

string clean_text(vector<string> vs){
    string aux = "";
    for(int i=0; i<vs.size(); i++){
        for(auto c : vs[i]){
            if(c < 'a' or c >'z') continue;
            aux += c;
        }
    }
    return aux;
}

int key_size(vector<string> data){
    int count=0;
    string text = clean_text(data);
    
    map<string, set<int>> trigramas;
    for(int i=0; i<text.size()-2; i++){
        string tri_a = text.substr(i, 3);
        for(int j=i+1; j<text.size()-2; j++){
            string tri_b = text.substr(j, 3);
            if(tri_a == tri_b){
                trigramas[tri_a].insert(j-i);
            }
        }
    }

    map<int, int> divs;
    for(auto trig: trigramas){
        set<int> distances = trig.second;
        for(auto d: distances){
            for(int i=2; i<=20; i++){
                if(d%i == 0){
                    divs[i]++;
                }
            }
        }
    }
    vector<pair<int,int>> greaters;
    int maior = 0;
    int save = 0;
    for(auto it: divs){
        greaters.pb(it);
    }
    auto ordena = [&] (pair<int,int> a, pair<int,int> b) {
        return tie(a.second, a.first) > tie(b.second, b.first);
    };
    sort(greaters.begin(), greaters.end(), ordena);

    cout<<"Possíveis tamanhos de chaves"<<endl;
    for(auto it: greaters){
        cout<<"Tamanho = "<<it.first<<" Ocorrências = "<<it.second<<endl;
    }
    int key_size = greaters[0].first;
    cout<<"O tamanho escolhido foi: "<<greaters[0].first<<endl;
    char opt;
    cout<<"Você deseja escolher o seu próprio tamanho de chave? (s/n)"<<endl;
    cin>>opt;
    while(tolower(opt) != 's' and tolower(opt) != 'n'){
        cout<<"Você deseja escolher o seu próprio tamanho de chave? (s/n)"<<endl;
        cin>>opt;
    }
    if(opt == 's'){
        cout<<"Escolha um tamanho entre 2 e 20"<<endl;
        int tamanho; cin>>tamanho;
        while(tamanho < 2 or tamanho >20){
            cout<<"Escolha um tamanho entre 2 e 20"<<endl;
            cin>>tamanho;
        }
        key_size = tamanho;
    }

    return key_size;
}

char get_letter(vector<double> probabilities, string lang){
    vector<double> en = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};
    vector<double> pt = {14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40, 0.02, 2.78, 4.74, 5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.21, 0.01, 0.47};

    vector<double> prob = (lang == "en" ? en : pt);

    double menor = 0x3f3f3f3f;
    char c;
    // shiftando e pegando a menor diferenca
    for(int i=0; i<26; i++){
        double diff = 0;
        for(int j=0; j<26; j++){
            diff += abs(probabilities[(i+j)%26] - prob[j]);
        }
        if(diff < menor){
            menor = diff;
            c = i + 'a';
        }
    }
    return c;
}
string get_key(int key_size, string message, string language){
    string key = "";
    for(int i=0; i<key_size; i++){
        int total = 0;
        vector<int> freq(26);
        for(int j=i; j<message.size(); j++){
            freq[message[j]-'a']++;
            total++;
        }
        vector<double> probabilities;
        for(int c=0; c<26; c++){
            double x = (double)(freq[c]/total)*100;
            probabilities.pb(x);
        }
        key += get_letter(probabilities, language);
    }
    return key;
}

vector<string> get_input(string string_file){
    vector<string> data;
    ifstream file;
    file.open(string_file, ios::in);
    if (file.is_open()){
        string line;
        string space = " ";
        while(getline(file, line)){
            size_t pos = 0;
            while ((pos = line.find(space)) != string::npos) {
                data.push_back(treat_string(line.substr(0, pos)));
                line.erase(0, pos + space.length());
            }
            data.push_back(treat_string(line));
        }
        file.close();
    }
    return data;
}

// colocando a senha do mesmo tamanho da messagem
string equal_key(string message, string key){
    string aux = "";
    int j = 0;
    for(int i=0; i<message.size(); i++){
        if(message[i] < 'a' or message[i] > 'z') aux += message[i];
        else{
            aux += key[j];
            j++;
            j %= key.size();
        }
    }
    return aux;
}

void cifrador(string key, string message){
    key = equal_key(message, key);

    // cifra de acordo com a tabela de vigenere
    string msg = "";
    for(int i=0; i<key.size(); i++){
        if(message[i] < 'a' or message[i] > 'z') msg += message[i];
        else msg += (((message[i]-'a') + key[i]-'a') % 26) + 'a';
    }
    cout << msg << endl;
}

void decifrador(string key, string message){
    key = equal_key(message, key);

    // decifra de acordo com a tabela de vigenere
    string msg = "";
    for(int i=0; i<message.size(); i++){
        if(message[i] < 'a' or message[i] > 'z') msg += message[i];
        else msg += ((((message[i]-'a')-(key[i]-'a')) + 26) % 26) + 'a';
    }
    cout << msg << endl;
}

int32_t main(){
    vector<string> dados = get_input("mensagem.txt");
    
    int op = 0;
    while(op != 1 and op != 2){
        cout << "Digite a opcao desejada:" << endl;
        cout << "1) Cifrador" << endl;
        cout << "2) Decifrador" << endl;
        cin >> op;
        if(op != 1 and op != 2){cout << "Opcao invalida!" << endl;}
    }
    if(op == 1){
        cout << "Digite uma chave para cifrar a mensagem, seguindo a Cifra de Vigenere: " << endl;
        string key; cin >> key;
        cout<<"Mensagem cifrada:"<<endl;
        cifrador(key, concat(dados));
    } else if(op == 2){
        cout<<"Selecione uma língua: (en/pt)"<<endl;
        string lang; cin>>lang;
        while(treat_string(lang) != "en" and treat_string(lang)!="pt"){
            cout<<"Selecione uma língua: (en/pt)"<<endl;
            cin>>lang;
        }
        lang = treat_string(lang);
        op = 0;
        while(op != 1 and op != 2){
            cout << "Digite a opcao desejada:" << endl;
            cout << "1) Decifrar com chave" << endl;
            cout << "2) Decifrar sem chave" << endl;
            cin >> op;
            if(op != 1 and op != 2){cout << "Opcao invalida!" << endl;}
        }
        if(op == 1){
            cout << "Digite uma senha para decifrar a mensagem, seguindo a Cifra de Vigenere: " << endl;
            string key; cin >> key;
            cout<<"Mensagem decifrada:"<<endl;
            decifrador(key, concat(dados));
        }else{
            int lenght_key = key_size(dados);
            cout<<"Tamanho da chave "<<lenght_key<<endl;
            string key = get_key(lenght_key, clean_text(dados), lang);
            cout<<"Chave estimada: "<<key<<endl;
            cout<<"Mensagem decifrada:"<<endl;
            decifrador(key, concat(dados));
            
        }
    }

    return 0;
}
