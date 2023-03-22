<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Template;
	use Proj\Site\Params;
	use Proj\Site\Units\General;

	abstract class Contacts {

		public static function ToVar(): string {
			Template::Start();
			self::Render();
			return Template::Read();
		}

		public static function Render(): void { ?>
			<div class = "view general contacts">
				<p><?= Params::$site_address; ?> – это молодой, развивающийся проект, который нуждается в Вашей <?= General::instance()->donations->GetLink('доброй поддержке', [], ['class' => 'link']); ?>, здоровой критике и пожеланиях по дальнейшему улучшению.</p>
				<p>По всем вопросам можно обратиться по электронному адресу: <b><?= Params::$support; ?></b>.</p>
			</div>
		<?php }

	}