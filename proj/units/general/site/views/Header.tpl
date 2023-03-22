<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Template;
	use Proj\Site\Units\General;
	use Proj\Site\Params;

	abstract class Header {

		public static function ToVar(): string {
			Template::Start();
			self::Render();
			return Template::Read();
		}

		public static function Render(): void { ?>
			<div class = "view general header">
				<div class = "agency">
					<div class = "logo"><?= General::instance()->home->GetLink(''); ?></div>
					<div class = "info">
						<div class = "name"><?= Params::$site_name; ?></div>
						<div class = "slogan">управляй своими документами</div>
					</div>
					<div class = "more">
						<div onclick = "$ui_menu.Open();">
							<div></div>
							<div></div>
							<div></div>
						</div>
					</div>
				</div>
				<div class = "menu">
					<div>
						<div><?= General::instance()->home->GetLink('Главная'); ?></div>
						<div><?= General::instance()->about->GetLink('О проекте'); ?></div>
						<div><?= General::instance()->contacts->GetLink('Контакты'); ?></div>
					</div>
				</div>
			</div>
		<?php }

	}