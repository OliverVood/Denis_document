<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Buffering;
	use Proj\Site\Actions;
	use Proj\Params;

	abstract class About {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
		}

		public static function Render(): void { ?>
			<div class = "view general about">
				<p>Дорогой пользователь, Вы находитесь на ресурсе созданным одним человеком. Я рад, что мой ресурс приносит пользу.</p>
				<p>Я буду развивать проект и в дальнейшем. Планы по развитию такие, что сам Наполеон Бонапарт позавидовал бы. Но, конечно, без Вашего участия у меня ничего не получится. Если Вы хотите поддержать проект, то можете кликнуть <?= Actions\General::$donations->GetLinkHref('тут', [], ['class' => 'link']); ?>, если хотите покритиковать, выразить признательность, дать дельный совет, стать моим партнёром или спонсировать на особых условиях, то пишите сюда: <?= Params::$support ?>.</p>
			</div>
		<?php }

	}