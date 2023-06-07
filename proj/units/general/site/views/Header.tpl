<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Buffering;
	use Proj\Params;
	use Proj\Site\Actions;

	abstract class Header {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
		}

		public static function Render(): void { ?>
			<div class = "view general header">
				<div class = "agency">
					<div class = "logo"><?= Actions\General::$home->GetLinkHref(''); ?></div>
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
						<div><?= Actions\General::$home->GetLinkHref('Главная'); ?></div>
						<div><?= Actions\General::$about->GetLinkHref('О проекте'); ?></div>
						<div><?= Actions\General::$contacts->GetLinkHref('Контакты'); ?></div>
					</div>
				</div>
			</div>
		<?php }

	}