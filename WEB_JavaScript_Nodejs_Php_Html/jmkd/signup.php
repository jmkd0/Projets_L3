<style>
  body{
    background-image: url('ressource/image_ia.jpg');
    color:white;
  }
</style>
<form class="needs-validation"  action="signup_control.php" enctype= "multipart/form-data" method="post">
        <div class="form-group">
            <label for="exampleInputEmail1">Votre nom :</label>
            <input type="text" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp" placeholder="jean" name="name" required>
            <small id="emailHelp" class="form-text text-muted">Votre nom.</small>
            </div>
          <div class="form-group">
            <label for="exampleInputEmail1">Identifiant ou Email :</label>
            <input type="text" class="form-control" id="exampleInputEmail1" aria-describedby="emailHelp" placeholder="dzoumegno21@gmail.com" name="email" required>
            <small id="emailHelp" class="form-text text-muted">Votre identifiant ou email.</small>
            </div>
            <div class="form-group">
              <label for="exampleInputPassword1">Mot de passe : </label>
              <input type="password" class="form-control" id="exampleInputPassword1" placeholder="Mot de passe" name="password" required>
            </div>
          <div>
           <label for="inputState1" class="labelo">Type de sujet, Examen, Devoir ou autre: </label>
            <select id="inputState1" class="form-control" name="type_sujet" required>
              <option selected value="0"> Choisir</option>
              <option value="devoir">Devoir</option>
              <option value="examen">Examen</option>
              <option value="autre">Autre</option>
            </select>
          </div>
          <div>
           <label for="inputState3" class="labelo">Choisissez le semestre: </label>
            <select id="inputState3" class="form-control" name="ue_matiere" required>
              <option selected value="0"> Choisir</option>
              <option selected value="1"> Devoir 1</option>
            </select>
          </div>
          <div class="form-group">
            <label for="exampleFormControlFile1" class="labelo">Chisir un fichier: Max: 3Mo</label>
            <input type="file" class="form-control-file" name = "file" id="exampleFormControlFile1" required>
          </div>
          <br>
            <button type="submit" name = "signin" class="btn btn-primary btn-lg valid" style="position: relative; margin-left: 35%;">Envoyer</button>
          <br>
</form>