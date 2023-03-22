<?php

	namespace Proj\Admin\Templates\Users;

	use Base\Templates\Template;
	use Proj\Admin\Units\Users;

	abstract class FormAuthorization {

		public static function ToVar(): string {
			Template::Start();
			self::Render();
			return Template::Read();
		}

		public static function Render(): void { ?>
			<div class = "view users form_authorization">
				<form action = "<?= Users::instance()->auth->GetPath(); ?>">
					<input type = "text" name = "login">
					<input type = "password" name = "password">
					<input type = "submit" value = "Войти" onclick = "<?= Users::instance()->auth->GetClick(); ?>">
				</form>
			</div>
		<?php }

	}