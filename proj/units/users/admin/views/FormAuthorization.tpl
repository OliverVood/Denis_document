<?php

	namespace Proj\Admin\Templates\Users;

	use Base\Templates\View;
	use Proj\Admin\Units\Users;

	class FormAuthorization extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render(): void { ?>
			<div class = "view users form_authorization">
				<form action = "<?= Users::instance()->auth->GetPath(); ?>">
					<input type = "text" name = "login">
					<input type = "password" name = "password">
					<input type = "submit" value = "Войти" onclick = "<?= Users::instance()->auth->GetClick(); ?>">
				</form>
			</div>
		<?php }

	}