<?php

	namespace Proj\Site\Templates\Feedback;

	use Base\Templates\Buffering;
	use Proj\Site\Actions;

	abstract class Form {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
		}

		public static function Render(): void { ?>
			<div class = "view feedback form">
				<form action = "/feedback/do">
					<div>
						<label><span class = "required">Имя</span></label>
						<input name = "name" type = "text" maxlength = "255">
					</div>
					<div>
						<label>Контакты</label>
						<input name = "contacts" type = "text" maxlength = "255">
					</div>
					<div>
						<label>Тема</label>
						<input name = "letter" type = "text" maxlength = "255">
					</div>
					<div>
						<label><span class = "required">Содержание</span></label>
						<textarea name = "content" rows = "4"></textarea>
					</div>
					<div>
						<input type = "submit" onclick = "<?= Actions\Feedback::$do_feedback->GetClick(); ?>">
					</div>
				</form>
			</div>
		<?php }
	}