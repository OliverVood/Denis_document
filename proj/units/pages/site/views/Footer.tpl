<?php

	namespace Proj\Site\Templates\Pages;

	use Base\Templates\Buffering;
	use Proj\Params;
	use Proj\Site\Actions;

	abstract class Footer {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
		}

		public static function Render(): void { ?>
			<div class = "view general footer">
				<div>
					<div class = "agency">
						<div class = "logo"><?= Actions\Pages::$home->GetLinkHref(''); ?></div>
						<div class = "info">
							<div class = "name"><?= Params::$site_name; ?></div>
							<div class = "slogan">управляй своими документами</div>
						</div>
					</div>
					<div class = "menu">
						<div><?= Actions\Feedback::$feedback->GetLinkHref('Обратная связь'); ?></div>
						<div><?= Actions\Pages::$donations->GetLinkHref('Поддержать проект'); ?></div>
						<div><?= Actions\Pages::$privacy_policy->GetLinkHref('Политика конфиденциальности'); ?></div>
						<div><?= Actions\Pages::$terms_use->GetLinkHref('Пользовательское соглашение'); ?></div>
					</div>
				</div>
			</div>
		<?php }

	}