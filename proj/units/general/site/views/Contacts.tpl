<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Buffering;
	use Proj\Params;
	use Proj\Site\Actions;

	abstract class Contacts {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
		}

		public static function Render(): void { ?>
			<div class = "view general contacts">
				<p><?= Params::$site_address; ?> – это молодой, развивающийся проект, который нуждается в Вашей <?= Actions\General::$donations->GetLinkHref('доброй поддержке', [], ['class' => 'link']); ?>, здоровой критике и пожеланиях по дальнейшему улучшению.</p>
				<p>По всем вопросам можно обратиться по электронному адресу: <b><?= Params::$support; ?></b>.</p>
			</div>
		<?php }

	}